import os
import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Ensure environment variable is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    user_id = session["user_id"]
    u = db.execute("SELECT username FROM users WHERE id = :id", id=user_id)
    username = u[0]['username']
    information = db.execute("SELECT symbol, shares,price, cash FROM transactions where username = :username", username=username)
    c = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)
    cash = c[0]['cash']
    count = len(information)
    items = ["symbol", "shares", "price", "cash"]
    """Show portfolio of stocks"""
    return render_template("index.html", information= information, count=count, cash = cash)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Missing Symbol")
        if not request.form.get("quantity"):
            return apology("Missing quantity")
        """Buy shares of stock"""
        symbol = request.form.get("symbol")
        symbol = symbol.upper()
        quantity= int(request.form.get("quantity"))
        info = lookup(symbol)
        print(info)
        if not info:
            return apology("Not Found")
        price = info['price']
        if not price:
            return apology("Price not found")
        total_amount = float(price * quantity)
        total_amount = round(total_amount ,2)
        user_id = session["user_id"]
        name = db.execute("SELECT username FROM users WHERE id = :id", id=user_id)
        username = name[0]['username']
        quantity = int(quantity)
        print(username)
        # user_id = db.execute("SELECT id FROM users WHERE username = :username", username = username)
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)
        if cash[0]['cash'] < total_amount:
            return apology("Low on cash")
        time = datetime.datetime.now()
        # portfolio = db.execute("CREATE TABLE 'transactions'('id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,'username' TEXT NOT NULL , 'symbol' TEXT NOT NULL, 'shares' INTEGER NOT NULL, 'price' INTEGER NOT NULL, 'cash' INTEGER NOT NULL, 'date' DATE NOT NULL)")
        db.execute("INSERT INTO 'transactions' (username, symbol,shares,price, cash, date) VALUES (:username , :symbol, :shares, :price, :cash, :date)" , username=username, symbol=symbol, shares=quantity, price = price, cash=total_amount, date = time)
        db.execute("UPDATE users SET cash = cash - :total_amount WHERE id = :id", total_amount=total_amount, id = user_id)

        particulars = "BOUGHT"
        db.execute("INSERT INTO 'history' (particulars, symbol, shares , price , date, user_id) VALUES (:particulars, :symbol, :shares, :price,:date, :user_id)",
                    particulars = particulars, symbol=symbol, shares= quantity, price=price, date=time , user_id = user_id)

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session['user_id']
    info = db.execute("SELECT particulars, symbol, price , shares, date FROM history WHERE user_id = :user_id", user_id = user_id)
    count = len(info)
    print(info)
    return render_template("history.html", info = info , count = count)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Missing symbol")
        symbol = request.form.get("symbol")
        info = lookup(symbol)
        price = info['price']
        symbol = info['symbol']
        if not info:
            return apology("No information found")
        return render_template("displayQuote.html", price= price, symbol=symbol)
    return render_template("quote.html")
    """Get stock quote."""


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == 'POST':
        if not request.form.get("username"):
            return apology("Missing username")
        if not request.form.get("password"):
            return apology("Missing password")
        if not request.form.get("confirmation"):
            return apology("Please confirm your password")
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Password not match")

        username = request.form.get("username")
        rows = db.execute("SELECT username FROM users WHERE username = :username",
                username=username)
        if len(rows) == 1:
            return apology("User already exist")
        password = request.form.get("password")
        hashed = generate_password_hash(password)
        result = db.execute("INSERT INTO users (username , hash) VALUES (:username, :hash)",
                username=username,hash=hashed)  # insert username and hashed password into database
        if not result:
            return apology("Some error occured")

        user_id = db.execute("SELECT id FROM users WHERE username = :username",
                    username = username)
        session["user_id"] = user_id
        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    users = db.execute("SELECT username FROM users WHERE id= :id", id=user_id)
    username = users[0]['username']
    info = db.execute("SELECT id, symbol, shares FROM transactions WHERE username = :username", username = username)
    count = len(info)
    if request.method == "POST":
        stock = request.form.get("stock")
        print(stock)
        if not stock:
            return apology("Missing stock")
        quantity = int(request.form.get("quantity"))
        if not quantity:
            return apology("Missing quantity")
        s = db.execute("SELECT symbol, shares, price, date FROM transactions WHERE id = :id", id = stock)
        shares = s[0]['shares']
        symbol = s[0]['symbol']
        date_bought = s[0]['date']
        old_price = s[0]['price']
        print(quantity)
        print(shares)
        if (shares < quantity):
            return apology("Not many shares to sell")
        print(symbol)

        p = lookup(symbol)
        if not p:
            return apology("reload")
        print(p)
        price = p["price"]
        if not price:
            return apology("Price not found")
        tot = quantity * price
        total = round(tot, 2)
        change = db.execute("UPDATE transactions SET shares = shares - :shares WHERE id = :id", shares = quantity, id = stock)
        new = db.execute("SELECT shares, price FROM transactions WHERE id = :id", id= stock)
        new_share= new[0]['shares']
        new_total = old_price * new_share
        new_total = round(new_total, 2)
        db.execute("UPDATE transactions SET cash = :total WHERE id = :id", total = new_total, id = stock)
        h_date = datetime.datetime.now()
        particulars = "SOLD"
        db.execute("INSERT INTO history (particulars, symbol, price , shares, date, user_id) VALUES (:particulars, :symbol, :price, :shares, :date, :user_id)",
                    particulars= particulars, symbol=symbol, price=price,shares=quantity ,date= h_date, user_id = user_id)
        total = int(total)
        cash = db.execute("UPDATE users SET cash = cash + :total WHERE id = :id", total = total, id=user_id)
        db.execute("DELETE FROM transactions WHERE shares = 0")
        return redirect("/")

    return render_template("sell.html", info=info , count = count)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
