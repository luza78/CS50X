import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # Gets the user input from form, and stores in variables. Convert date and month to int, as all the .get data is STR
        bdayname = request.form.get("bdayname")
        bdayday = request.form.get("bdayday")
        bdaymonth = request.form.get("bdaymonth")
        bdayday = int(bdayday)
        bdaymonth = int(bdaymonth)

        db.execute("INSERT INTO birthdays(name, day, month) VALUES (?, ?, ?);", bdayname, bdayday, bdaymonth)

        return redirect("/")

    else:

        # Select all from birthdays, and stores it in a variable, ordering by date,
        # passes it into the jinja variable in index file
        birthdays = db.execute("SELECT * FROM birthdays ORDER BY month, day;")

        return render_template("index.html", birthdays=birthdays)


# Deletes an entry from DB
@app.route("/delete", methods=["POST"])
def delete():
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM birthdays WHERE id = ?;", id)
    return redirect("/")

# Routes to edit page
@app.route("/edit", methods=["POST"])
def edit():
    idedit = request.form.get("iddate")
    if idedit:
        editbirthday= db.execute("SELECT * FROM birthdays WHERE id = ?;", idedit)
        return render_template("edit.html", editbirthday=editbirthday)


# Updates the dates of selected candidate once submit is pressed
@app.route("/editconfirm", methods=["POST"])
def editconfirm():
    bdayname = request.form.get("bdayname")
    bdayday = request.form.get("bdayday")
    bdaymonth = request.form.get("bdaymonth")
    bdayid = request.form.get("bdayid")

    bdayday = int(bdayday)
    bdaymonth = int(bdaymonth)
    bdayid= int(bdayid)

    db.execute("UPDATE birthdays SET day=?, month=? WHERE id = ?;", bdayday, bdaymonth, bdayid)
    return redirect("/")