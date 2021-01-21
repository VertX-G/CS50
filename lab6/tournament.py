# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # TODO: Read teams into memory from file

    # declare 'filename' variable to record user input
    filename = sys.argv[1]

    # declare list for teams
    teams = []

    # open the .csv in read mode
    with open(filename, "r") as file:
        # read with .DictReader
        # reads each row as a dictionary
        # with the header row as the key names
        reader = csv.DictReader(file)
        # iterate over each row
        for row in reader:
            # iterate over the keys in the dictionary
            for key in row:
                # change the value of 'rating' to an int
                row['rating'] = int(row['rating'])

            # add the dictionary to the list
            teams.append(row)

    # declare variable to keep count of teams for testing
    teamCount = 0
    # test print the list
    for team in teams:
        print(team)
        teamCount += 1
    print(f"Team Count = {teamCount}")


    # call simulate_tournament function

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    # call simulate_tournament function

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # call simulate_round function, accepts a list of teams and returns a list of winners
    # Repeatedly simulate round until only one team is left
    # return name of winning team to be used in counts dictionary


if __name__ == "__main__":
    main()
