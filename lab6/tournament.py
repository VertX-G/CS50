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

    '''
    # test print the list of teams dictionaries
    for team in teams:
        print(f"Teams = {team}")
    print()
    '''

    # declare a dictionary to hold the names of the teams and number of times they have won
    counts = {}

    # OPTION 1:
    # add all teams to the dictionary
    # iterate through list of team dictionaries
    for team in teams:
        # for each 'team' dictionary in the list of 'teams' dictionaries
        # add to the 'counts' dictionary
        # the name of the current 'team' as the key, and 0 as value
        # dictionaryName[CurrentListItem[keyName]]
        counts[team['team']] = 0
        '''
        # test print for each line
        print(f"Line = {team}")
    print()
    '''
    '''
    # OPTION 2:
    # add all teams to the dictionary
    # iterate through list of team dictionaries
    for i in range(len(teams)):
        # for each 'team' dictionary in the list of 'teams' dictionaries
        # add to the 'counts' dictionary
        # the name of the current 'team' as the key, and 0 as value
        # dictionaryName[listName[listIndex][keyName]]
        counts[teams[i]['team']] = 0

        # test print for each line
        print(f"Line = {teams[i]}")
    print()
    '''
    '''
    # test print 'counts' dictionary to see if all teams have been added
    for item in counts.items():
        print(f"Populated Counts = {item}")
    print()
    '''
    # TODO: Simulate N tournaments and keep track of win counts
    for i in range(N):

        # run a simulation of the tournament
        # and save the name of the winner in 'winner'
        winner = simulate_tournament(teams)

        # if the winner exists in the dictionary
        # add a win to their count
        if winner in counts:
            counts[winner] += 1

        # if the winner does not exist in the dictionary
        # create a dictionary item for the winner
        # and add the win to their count
        else:
            counts[winner] = 1

    '''
    #  test print each team and number of times they won
    for item in counts.items():
        print(f"Calculated Counts = {item}")
    print()
    '''

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

    # declare variable to hold winning teams and ultimate winner
    winner = teams

    # loop until ultimate winner is found
    while True:
        winner = simulate_round(winner)

        # if only 1 team left in 'winner', then its the ultimate winning team
        if len(winner) == 1:
            break

    # grab only the name of the winning team
    winnerName = winner[0].get('team')
    # return the name of the winning team
    return winnerName


if __name__ == "__main__":
    main()
