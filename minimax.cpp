#include <iostream>

using namespace std

int minimax(position, int depth){
    if(depth == 0 || gameIsOver(position))
        return evaluation(position);
    if(maximizingPlayer){
        int maxEval = -infinity
        for each child of position
        {
            int maxEval = max(maxEval, minimax(child, depth-1))
        }
        return maxEval
    }else{
        int minEval = +infinity
        for each child of position
        {
            minEval = min(minEval, minimax(child, depth-1))
        }
        return minEval;
    }
}
