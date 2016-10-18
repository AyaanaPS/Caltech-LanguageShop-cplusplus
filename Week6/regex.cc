#include "regex.hh"
#include <iostream>
#include <vector>
using namespace std;


/* Initialize the regex operator to apply exactly once. */
RegexOperator::RegexOperator(Type t)
{
    minRepeat = 1;
    maxRepeat = 1;
    type = t;
}

RegexOperator::Type RegexOperator::getType() const
{
    return type;
}

/* Returns the "minimum repeat count" value. */
int RegexOperator::getMinRepeat() const {
    return minRepeat;
}


/* Returns the "maximum repeat count" value. */
int RegexOperator::getMaxRepeat() const {
    return maxRepeat;
}


/* Sets the "minimum repeat count" value. */
void RegexOperator::setMinRepeat(int n) {
    assert(n >= 0);
    minRepeat = n;
}


/* Sets the "maximum repeat count" value. */
void RegexOperator::setMaxRepeat(int n) {
    assert(n >= -1);
    maxRepeat = n;
}


/* Clears the list of matches stored in the regex operator.  Typically done
 * in preparation to try to match the regex to a new string.
 */
void RegexOperator::clearMatches() {
    matches.clear();
}


/* Records a new match of the operator in the list of matches. */
void RegexOperator::pushMatch(const Range &r) {
    matches.push_back(r);
}


/* Reports how many times the regex operator has successfully matched in the
 * string.
 */
int RegexOperator::numMatches() const {
    return (int) matches.size();
}

/* Removes the last match the operator successfully matched against.  Used for
 * backtracking by the regex engine.
 */
Range RegexOperator::popMatch() {
    Range r = matches.back();
    matches.pop_back();
    return r;
}

MatchChar::MatchChar(char s) : RegexOperator(Type::MATCH_CHAR) {
    to_match = s;
}

bool MatchChar::match(const string &s, Range &r) const
{
    printf("In matchChar match\n");
    int sLen = s.length();
    if(r.start >= sLen)
    {
        return false;
    }

    if(to_match == s[r.start])
    {
        printf("Found CharMatch\n");
        r.end = r.start + 1;
        return true; 
    }
    printf("Found CharMismatch\n");
    return false;
}

MatchAny::MatchAny() : RegexOperator(Type::MATCH_ANY) {

}

bool MatchAny::match(const string &s, Range &r) const
{
    printf("In matchAny match\n");
    int sLen = s.length();
    if(r.start >= sLen)
    {
        return false;
    }
    printf("Found AnyMatch\n");
    r.end = r.start + 1;
    return true;
}

MatchFromSubset::MatchFromSubset(string &s) : RegexOperator(Type::MATCH_SUBSET)
{
    subset = s;
}

bool MatchFromSubset::match(const string &s, Range &r) const
{
    printf("In SubsetMatch match\n");
    int sLen = s.length();
    int subLen = subset.length();
    if(r.start >= sLen)
    {
        return false;
    }

    for(int i = 0; i < subLen; i++)
    {
        if(subset[i] == s[r.start])
        {
            printf("Found SubsetMatch\n");
            r.end = r.start + 1;
            return true;
        }
    }   
    printf("Found SubsetMismatch\n");
    return false;
}

ExcludeFromSubset::ExcludeFromSubset(string &s) : RegexOperator(Type::EXCLUDE_SUBSET)
{
    subset = s;
}

bool ExcludeFromSubset::match(const string &s, Range &r) const
{
    printf("In ExcludedMatch match\n");
    int sLen = s.length();
    int subLen = subset.length();
    if(r.start >= sLen)
    {
        return false;
    }

    for(int i = 0; i < subLen; i++)
    {
        if(subset[i] == s[r.start])
        {
            printf("Found Match in Excluded - Bad\n");
            return false;
        }
    }   
    printf("Found none from Excluded - Good\n");
    r.end = r.start + 1;
    return true;
}

vector<RegexOperator *> parseRegex(const string &expr)
{
    int sLen = expr.length();
    vector<RegexOperator *> result;
    bool escape = 0; //0 if not being escaped, 1 if being escaped
    bool bracket = 0; //0 if not in bracket, 1 if in bracket
    bool negateBracket = 0;
    string inBracket = "";

    for(int i = 0; i < sLen; i++)
    {  
        if(bracket == 0)
        {
            if(expr[i] == '\\')
            {
                if(escape == 0)
                {
                    escape = 1;
                    MatchChar op1 = MatchChar('\\');
                    result.push_back(&op1);
                }
                else
                {
                    escape = 0;
                }
            }

            else if(expr[i] == '.')
            {
                if(escape == 0)
                {
                    MatchAny op1 = MatchAny();
                    result.push_back(&op1);
                }
                else
                {
                    escape = 0;
                    result.pop_back();

                    MatchChar op1 = MatchChar('.');
                    result.push_back(&op1);
                }
            }

            else if(expr[i] == '?')
            {
                if(escape == 0)
                {
                    result.back()->setMinRepeat(0);
                }
                else
                {
                    escape = 0;
                    result.pop_back();

                    MatchChar op1 = MatchChar('?');
                    result.push_back(&op1);
                }
            }

            else if(expr[i] == '*')
            {
                if(escape == 0)
                {
                    result.back()->setMinRepeat(0);
                    result.back()->setMaxRepeat(-1);
                }
                else
                {
                    escape = 0;
                    result.pop_back();

                    MatchChar op1 = MatchChar('*');
                    result.push_back(&op1);
                }
            }

            else if(expr[i] == '+')
            {
                if(escape == 0)
                {
                    result.back()->setMaxRepeat(-1);
                }
                else
                {
                    escape = 0;
                    result.pop_back();

                    MatchChar op1 = MatchChar('+');
                    result.push_back(&op1);
                }
            }

            else if(expr[i] == '[')
            {
                bracket = 1;
            }

            else
            {
                escape = 0;
                MatchChar op1 = MatchChar(expr[i]);
                result.push_back(&op1);
            }

        }

        else
        {
            if(expr[i] == ']')
            {
                if(negateBracket == 1)
                {
                    negateBracket = 0;
                    ExcludeFromSubset op1 = ExcludeFromSubset(inBracket);
                    result.push_back(&op1);
                }
                else
                {
                    MatchFromSubset op1 = MatchFromSubset(inBracket);
                    result.push_back(&op1);
                }

                bracket = 0;
                inBracket = "";
            }
            else if(expr[i] == '^')
            {
                negateBracket = 1;
            }
            else
            {
                inBracket = inBracket + expr[i];
            }
        }
    }

    return result;
}

void clearRegex(vector<RegexOperator *> regex)
{
    while(regex.size() > 0)
    {
        regex.pop_back();
    }
}






