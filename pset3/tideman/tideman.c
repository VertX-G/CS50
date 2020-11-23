#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int test_cand;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void sort(int l, int r);
void merge(int l, int m, int r);
bool check_cycle(int l);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

/*
    TIDEMAN VOTE
    TALLY: Once voters have indicated preferences, determine winner for each pair of candidates
    SORT: Sort pairs of candidates in decreasing strength of victory
    LOCK: starting with strongest pair, "lock in" each pair to candidate graph as long as no cycles occur
    WINNER: of election is the source of the graph - we may assume that there will not be more than one source
*/

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // CHECK IF CANDIDATES NAME EXISTS
    // Iterate through list of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If the vote name matches a candidate name
        if (strcmp(name, candidates[i]) == 0)
        {
            // Update voter's [i]th preference of candidate
            ranks[rank] = i;

            return true;
        }
    }

    // If candidate's name does not exist - If vote != a valid candidate
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    /*
        Update the preferences array based on the current voter's ranks
        For ranks [3][0][4][1][2]
        candidate 3 is preferred over candidates 0,4,1,2
        candidate 0 is preferred over candidates 4,1,2
        candidate 4 is preferred over candidates 1,2
        candidate 1 is preferred over candidate 2
        candidate 2 is not preferred over anyone
    */
    // Iterate through the 2D array in decending order of preference and add 1 to each preferred candidate matchup
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = (i + 1); j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    /*
        // Test that prints out the entire 'preferences' 2D array
        for (int i = 0; i < candidate_count; i++)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                printf("%i", preferences[i][j]);
            }
            printf("\n");
        }
    */
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;

    // Iterate through each possible pair
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // If that pair has one candidate that is pereferred over another, and if they are not tied
            if (preferences[i][j] > 0 && preferences [i][j] > preferences [j][i])
            {
                // add them to the pairs array
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                /*
                    // Test to check pairs are generated correctly
                    printf("Pair%i\nWinner = %i\nLoser = %i\n", pair_count, pairs[pair_count].winner, pairs[pair_count].loser);
                */
                // Add to the pair count
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Sort pairs in order by decrease strength of victory (the larger the difference between the winner and loser)
    // preferences[winner][loser] gives the strength of victory

    // Call the 'sort' function with the position of the first and last elements in the 'pairs' array
    sort(0, pair_count - 1);

    /*
        // Test Print
        for (int i = 0; i < pair_count; i++)
        {
            printf("\nPair %i:\nWinner: %i\nLoser: %i\nStrength of Victory:%i\n", i, pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser]);
        }
    */
    return;
}

// Mergesort the pairs
void sort(int l, int r)
{
    if (l < r)
    {
        // Find mid element
        int m = (l + r) / 2;

        // Call function again to recursively sort both halves
        sort(l, m);
        sort(m + 1, r);

        // Merge the array
        merge(l, m, r);
    }
}

// Merge two subarrays
void merge(int l, int m, int r)
{
    int i, j, k;

    // Record number of items in each subarray
    int n1 = m - l + 1;     // First subarray is arr[l..m]
    int n2 = r - m;         // Second subarray is arr[m+1..r]

    // Create temp arrays
    pair L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
    {
        L[i] = pairs[l + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = pairs[m + 1 + j];
    }

    // Mergesort temp arrays back to main array
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray

    while (i < n1 && j < n2)
    {
        // preferences[pairs[i].winner][pairs[i].loser]
        int pL = preferences[L[i].winner][L[i].loser];
        int pR = preferences[R[j].winner][R[j].loser];
        if (pL <= pR)
        {
            pairs[k] = R[j];
            j++;
        }
        else
        {
            pairs[k] = L[i];
            i++;
        }
        k++;
    }

    // Copy remaining elements of L[], if there are any remaining
    while (i < n1)
    {
        pairs[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[], if there are any remaining
    while (j < n2)
    {
        pairs[k] = R[j];
        j++;
        k++;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // after pairs are sorted, start locking them from the pair with the largest strength of victory downward
    // do not lock if locking will result in cycle

    // Iterate through the 'pairs' array
    for (int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner;
        int l = pairs[i].loser;
        test_cand = w;

        // lock the pair if it doesnt create a cycle
        if (check_cycle(l) != true)
        {
            locked[w][l] = true;

            // Test Print
            //printf("Locked %i -> %i\n", w, l);
        }
        /*
            // Test Print
            else
            {
                printf("Did not lock %i -> %i\n", w, l);
            }
        */
    }
    return;
}

// check whether locking the pair will create a cycle in the graph
bool check_cycle(int l)
{

    // Receive the losing candidate in the pair currently being tested
    // check each of the other possible pairs with the candidate as the winner to see if an arrow has been locked
    for (int i = 0; i < MAX; i++)
    {
        // if an arrow has been locked, see if the loser is the original winner being tested for
        if (locked[l][i] == true)
        {
            if (i == test_cand)
            {
                // if this loser is the original winner, then it creates a cycle
                return true;
            }
            // if this loser is not the original winner, check the possible pairs where this loser is the winner
            if (check_cycle(i) == true)
            {
                return true;
            }
        }
    } // if there was no cycle in this branch, check the next possible pair

    // if no pair with a cycle was found, return false
    return false;

}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // Winner is source of the graph
    // source of the graph is the only column in the 'locked' array that has no 'true' values

    /*
        // Test Print
        for(int i = 0; i < MAX; i++)
        {
            for(int j = 0; j < MAX; j++)
            {
                printf("%i", locked[i][j]);
            }
            printf("\n");
        }
    */

    for (int i = 0; i < MAX; i++)
    {
        bool check = false;
        for (int j = 0; j < MAX; j++)
        {
            if (locked[j][i] == true)
            {
                check = true;
            }
        }

        if (check == false)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}