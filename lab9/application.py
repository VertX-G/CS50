'''
TODO:

DONE 1. in application.py, query for all birthdays and pass that data to index.html (in the get request)
DONE 2. in index.html, render each birthday as a row in the table
DONE 3. in index.html, add a form to let users add a new birthday
DONE 4. in application.py, when the form submission is received, insert the birthday into the database
'''

import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # Retrieve user input from form
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Add birthday to database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        # Query database for all birthdays
        birthdays = db.execute("SELECT * FROM birthdays")

        # Render each birthday as a row in the table
        return render_template("index.html", birthdays=birthdays)


