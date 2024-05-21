is tie
int notelim = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == false)
        {
            notelim++;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        int mincan = 0;
        if ((!candidates[i].eliminated) && (candidates[i].votes == min))
        {
            mincan++;
        }
        if (mincan == notelim)
        {
            return true;
        }
    }
    return false;



    tabutulate
                for (int k = 1; k < candidate_count; k++)
                {
                    if (candidates[vote].eliminated == true)
                    {
                        vote++;
                    }
                    else
                    {
                        candidates[vote].votes++;
                        break;
                    }
                }
            }
            else if (candidates[vote].eliminated == false)
            {
                candidates[vote].votes++;
                break;
            }


            find min
                int minvotes = 0;
    int i, j;
    for (i = 0; i < candidate_count; i++)
    {
        for (j = 1; j < candidate_count; j++)
        {
            if (candidates[i].eliminated == true)
            {
                j++;
                break;
            }
            if (candidates[j].eliminated == true)
            {
                continue;
            }
            if ((candidates[i].votes <= candidates[j].votes) && (minvotes <= candidates[i].votes))
            {
                minvotes = candidates[i].votes;
                break;
            }
        }

    }