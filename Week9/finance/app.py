import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    stocks = db.execute(
        "SELECT symbol, name, price, SUM(shares) as totalShares FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    total_value = cash
    for stock in stocks:
        total_value += stock["price"] * stock["totalShares"]
    return render_template("index.html", stocks=stocks, cash=cash, total_value=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        # get input symbol and find stock and validate
        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)
        if not symbol:
            return apology("Please enter a symbol")
        elif not stock:
            return apology("Symbol not found")
        # get input shares amount and validate
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Shares must be numeric")
        if shares <= 0:
            return apology("Shares must be positive")
        #
        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        stock_name = stock["name"]
        stock_price = stock["price"]
        total_price = shares * stock_price

        if cash < total_price:
            return apology("Not enough $$$")
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total_price, user_id)
            db.execute("INSERT INTO transactions (user_id, name, shares, price, transaction_type, symbol) VALUES (?, ?, ?, ?, ?, ?)",
                       user_id, stock_name, shares, stock_price, 'BUY', symbol)
        return redirect('/')


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute("SELECT transaction_type, symbol, price, shares FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", transactions=transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        # get input symbol
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Please enter a Stock symbol")
        # get stock for symbol
        stock = lookup(symbol)
        if not stock:
            return apology("No stock found")
        # render stock information page
        return render_template("quoted.html", stock=stock)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    # if Register Button clicked, try to register user
    else:
        # get input information
        username = request.form.get('username')
        password = request.form.get('password')
        confirmation = request.form.get('confirmation')

        # if inputs do not meet requirements render apology
        if not username:
            return apology("Please enter a username")
        elif not password:
            return apology("Please enter a password")
        elif not confirmation:
            return apology("Please confrim your password")
        elif password != confirmation:
            return apology("Passwords do not match")

        # save inputs to database
        pwHash = generate_password_hash(password)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, pwHash)
        except:
            # if username already taken render apology (not sure how this works)
            return apology("Username already taken")
        return redirect('/')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "GET":
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
        return render_template("sell.html", symbols=symbols)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if shares <= 0:
            return apology("You must sell a positive number of shares")

        stock_price = lookup(symbol)["price"]
        stock_name = lookup(symbol)["name"]
        total_price = shares * stock_price

        shares_owned = db.execute(
            "SELECT shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)[0]["shares"]

        if shares_owned < shares:
            return apology("Not enough shares")

        current_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash + total_price, user_id)
        db.execute("INSERT INTO transactions (user_id, name, shares, price, transaction_type, symbol) VALUES(?, ?, ?, ?, ?, ?)",
                   user_id, stock_name, -shares, stock_price, "SELL", symbol)

        return redirect("/")

