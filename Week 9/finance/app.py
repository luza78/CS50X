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
    # How much cash the user has
    portfolio_cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
    portfolio_value = portfolio_cash[0]["cash"]
    portfolio_cash = portfolio_cash[0]["cash"]

    # Get unique names of stock owned by user
    portfolio = db.execute("SELECT name, quantity_owned FROM stocks WHERE user_id = ? AND quantity_owned > 0;", session["user_id"])

    if portfolio:
        # Loop through all unique symobls, finding their price, adding curren_price to dict
        for i in range(len(portfolio)):
            stock = lookup(portfolio[i]['name'])
            portfolio[i]['current_price'] = stock['price']
            portfolio[i]['current_total_price'] = 0.0

            # Find the total based on all owned stocks' current price
            portfolio[i]['current_total_price'] += portfolio[i]['current_price'] * portfolio[i]['quantity_owned']
            portfolio_value += portfolio[i]['current_total_price']

            # Clear dict before loop continues
            dict.clear(stock)

        return render_template("index.html",
                               portfolio_cash=portfolio_cash, portfolio_value=portfolio_value,
                               portfolio=portfolio)
    else:
        return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        user_input = (request.form.get("shares"))
        if not user_input:
            return apology("Error, no input")

        if not user_input.isnumeric():
            return apology("Invalid quantity selected. Must be whole numbers")
        user_input = int(user_input)

        if not user_input > 0:
            return apology("Must enter a positive number")
        stock = lookup(request.form.get("symbol"))
        quantity = request.form.get("shares")
        quantity = int(quantity)

        # Check if stock exists in lookup
        if not stock:
            return apology("Stock not found")

        # See how much cash the purchaser has, and then process the transaction accordingly
        price = float(stock["price"])
        transaction_cost = price * quantity
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
        if user_cash[0]["cash"] > transaction_cost:

            # User has enough cash, proceeding with transaction, updating the database
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?;", transaction_cost, session["user_id"])

            user_has_stock = db.execute("SELECT * from stocks WHERE user_id = ? AND name = ?;", session["user_id"], stock["name"])

            if not user_has_stock:
                db.execute("INSERT INTO stocks(user_id, name, quantity_owned) VALUES(?, ?, ?);",
                           session["user_id"], stock["name"], quantity)
                stock_id = db.execute("SELECT id from stocks WHERE user_id = ? AND name = ?;", session["user_id"], stock["name"])
                db.execute("INSERT INTO history(user_id, stock_id, quantity, price) VALUES (?, ?, ?, ?);",
                           session["user_id"], stock_id[0]["id"], quantity, price)

            else:
                current_quantity = db.execute(
                    "SELECT quantity_owned FROM stocks WHERE user_id = ? AND name = ?;", session["user_id"], stock["name"])

                new_quantity = quantity + current_quantity[0]["quantity_owned"]
                db.execute("UPDATE stocks SET quantity_owned = ? WHERE user_id = ? AND name = ?;",
                           new_quantity, session["user_id"], stock["name"])

                stock_id = db.execute("SELECT id from stocks WHERE user_id = ? AND name = ?;", session["user_id"], stock["name"])

                db.execute("INSERT INTO history(user_id, stock_id, quantity, price) VALUES (?, ?, ?, ?);",
                           session["user_id"], stock_id[0]["id"], quantity, price)

            # Format to usd
            stock_price = usd(stock['price'])
            transaction_cost = usd(transaction_cost)
            quantity = "{:.2f}".format(quantity)
            cash_left = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
            cash_left = usd(cash_left[0]['cash'])

            flash("Bought " + str(quantity) + " " + stock['name'] + " for " + str(stock_price) +
                  " each and " + str(transaction_cost) + " total. You have " + str(cash_left) + " remaining.")
            return render_template("buy.html")

        else:
            return apology("Not enough cash, to process this transaction")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    history = db.execute(
        "SELECT *, type FROM stocks, history WHERE stocks.id = history.stock_id AND stocks.user_id = ?;", session["user_id"])

    return render_template("history.html", history=history)


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
    if request.method == "POST":

        # Look up stock

        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Stock not found")

        return render_template("quoted.html", stock=stock)

    # If get
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        # Checks if they entered a username or password
        if not request.form.get("username"):
            return apology("Choose a username")
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("Choose a password")
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("Passwords do not match")

        # Cheks if username is available
        exists = db.execute("SELECT username FROM users WHERE username = ?;", request.form.get("username"))
        if exists:
            return apology("Username is taken, try anither")

        # Adds user to db
        else:
            hash = generate_password_hash(request.form.get("password"))
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?);", request.form.get("username"), hash)

            # Gets ID and assigns session
            user = db.execute("SELECT id FROM users WHERE username = ? AND hash = ?;", request.form.get("username"), hash)
            session["user_id"] = user[0]["id"]
            return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    if request.method == "POST":
        # Qualifies valid input
        input_stock = request.form.get("symbol")
        if input_stock is None:
            return apology("Select stock")

        sell_quantity = request.form.get("shares")

        if sell_quantity is not None:
            if not sell_quantity.isdigit():
                return apology("Quantity error")

        stock = lookup(input_stock)

        if stock is None:
            return apology("Sorry, please select a stock")

        quantity_owned = db.execute("SELECT quantity_owned FROM stocks WHERE name = ? AND user_id = ?;",
                                    input_stock, session["user_id"])

        if not quantity_owned or quantity_owned is None:
            return apology("You can't sell more shares than you own")

        # Start transaction
        # Update Quantity
        db.execute("UPDATE stocks SET quantity_owned = quantity_owned - ? WHERE name = ? AND user_id = ?;",
                   sell_quantity, input_stock, session["user_id"])

        # Update cash
        transaction_total = stock['price'] * float(sell_quantity)
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?;", transaction_total, session["user_id"])

        # Insert history
        stock_id = db.execute("SELECT id FROM stocks WHERE name = ? AND user_id = ?;", input_stock, session["user_id"])

        db.execute("INSERT INTO History(stock_id, user_id, type, quantity, price) VALUES(?, ?, 'Sell', ?, ?);",
                   stock_id[0]["id"], session["user_id"], sell_quantity, stock['price'])

        # Success
        flash("Sold!")
        return redirect("/")

    # Populate options, based on stock currently only

    owned_stock_names = db.execute("SELECT name FROM stocks WHERE user_id = ? AND quantity_owned > 0;", session["user_id"])
    if not owned_stock_names:
        no_stock = "No stocks owned"
        return render_template("sell.html", no_stock=no_stock)

    return render_template("sell.html", symbols=owned_stock_names)


@app.route("/topup", methods=["GET", "POST"])
@login_required
def topup():
    if request.method == "POST":

        # Get user input
        amount = request.form.get("amount")

        # Validate input
        if not amount:
            return apology("Enter an amount")

        if not amount.isnumeric():
            return apology("Numeric characters only")

        # Change from str to float
        amount = float(amount)

        # Update user cash
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?;", amount, session["user_id"])

        # Add a success message
        amount = str(amount)
        success = "You successfully added $" + amount + " to your cash"
        return render_template("topup.html", success=success)
    return render_template("topup.html")
