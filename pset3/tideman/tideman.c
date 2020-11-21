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

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void sort(int l, int r);
void merge(int l, int m, int r);
bool check_cycle(int w, int l);

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
    WINNER: of election is the source of the graph
*/

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Check if candidate's name exists

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
    // Update the preferences array based on the current voter's ranks
    // For ranks [3][0][4][1][2]
    // candidate 3 is preferred over candidates 0,4,1,2
    // candidate 0 is preferred over candidates 4,1,2
    // candidate 4 is preferred over candidates 1,2
    // candidate 1 is preferred over candidate 2
    // candidate is not preferred over anyone

     for (int i = 0; i < candidate_count; i++)
    {
        //int j = i + 1;

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
    // pair_count = 0
    // Iterate through each possible pair
    // If preferences[i][j] > 0
    // pairs[pair_count](winner = i, loser = j)
    // pair_count++

    pair_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > 0 && preferences [i][j] > preferences [j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                // test print
/*
                // Test to check pairs are generated correctly
                printf("Pair%i\nWinner = %i\nLoser = %i\n", pair_count, pairs[pair_count].winner, pairs[pair_count].loser);
*/
                pair_count++;

            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // Sort pairs in order by decrease strength of victory (the larger the difference between the winner and loser)
    // i == pairs[pair_count].winner, j == pairs[pair_count].loser
    // preferences[i][j] gives the strength of victory

    // give each pairs[i] a rank
    // test sov againt each one that is already ranked and update ranks accordingly until it finds its spot
    // copy from pairs array into sov_arr temp array according to the determined ranks
    // then make pairs array equal to the sov_arr temp array

    // Make temp array for strength of victories (sov)


    sort(0, pair_count-1);

    // test print
/*
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
        int m = (l+r)/2;

        // Call function again to recursively sort both halves
        sort(l, m);
        sort(m+1, r);

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
   for(i = 0; i < n1; i++)
   {
       L[i] = pairs[l + i];
   }
   for(j = 0; j < n2; j++)
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
    // TODO
    // after pairs are sorted, start locking them from the largest difference pair downward
    // do not lock if locking will result in loop
    // do not create lock if loser column is the only one with no "true" in it

    for(int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner;
        int l = pairs[i].loser;

        // do not lock if it will result in a cycle
        // check if the loser of this pair is already the source
        // if it is not the source, lock the pair
        // if it is the source, do not lock
        if(check_cycle(w, l) == true)
        {
            return;
        }
        else
        {
            locked[w][l] = true;
        }
    }
    return;
}

// check whether the candidate is the source of the graph
bool check_cycle(int w, int l)
{

/*
    // If the column for the candidate passed contains any true values, it is not the source, return false
    for(int i = 0; i < pair_count; i++)
    {
        if(locked[i][candidate] == true)
        {
            return false;
        }
    }

    // if it does not contain any true values, it could be the source
    for(int i = 0; i < pair_count; i++)
    {
        if (i != candidate)
        {
            bool check = false;
            for(int j = 0; j < pair_count; j++)
            {
                if(locked[j][i] == true)
                {
                    check = true;
                }
            }

            // check whether any other columns also contain no true values
            // if they do, the passed candidate cannot be the source, return false
            if(check == false)
            {
                return false;
            }
        }
    }

    // if the return candidate column is the only one that contains no true values, it is the source, return true
    return true;

*/

    //Look at a pair
    //If the loser is not a winner in any existing locked pair, then lock the pair
    //If the loser is a winner in an existing locked pair:
    //Look at that pair
    //If the loser is not a winner in any existing locked pair, then lock the pair
    //If the loser is a winner in an existing locked pair:
    //Look at that pair
    //etc, etc etc . . .

    for(int i = 0; i < pair_count; i++)
    {
        if(locked[l][i] == true)
        {
            if(i == l)
            {
                return true;
            }
            check_cycle(l, i);
        }
    }
    return false;

}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // Winner is source of the graph
    // source of the graph is the only column in the 'locked' array that has no 'true' values

/*
    // print source using 'check source' function
    for(int i = 0; i < pair_count; i++)
    {
        if(check_cycle(i) == true)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
*/

    for(int i = 0; i < pair_count; i++)
    {
        bool check = false;
        for(int j = 0; j < pair_count; j++)
        {
            if(locked[j][i] == true)
            {
                check = true;
            }
        }

        if(check == false)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }

    // find winner using 'locked' array

/*
    string winner;

    for(int i = 0; i < pair_count; i++)
    {
        for(int j = 0; j < pair_count; j++)
        {
            if
        }
    }
*/
//    return;
}

