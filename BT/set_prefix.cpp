Boggle Solver: Finding Prefixes in a Set

Question:
This is for a homework assignment, so I don't want the exact code, but would appreciate any ideas that can help point me in the right direction. 
The assignment is to write a boggle solving program. I've got the recursive part down I feel, but I need some insight on how to compare the current sequence of characters to the dictionary.
I'm required to store the dictionary in either a set or sorted list. I've been trying a way to implement this using a set. In order to make the program run faster and not follow dead end paths, I need to check and see if the current sequence of characters exists as a prefix to anything in the set (dictionary).
I've found that set.find() operation only returns true if the string is an exact match. In the lab requirements, the professor mentioned that: 
"If the dictionary is stored in a Set, many data structure libraries provide a way to find the string in the Set that is closest to the one you are searching for. Such an operation could be used to quickly find a word with a given prefix."
I've been searching today for a what the professor is describing. I've found a lot of information on tries, but since I'm required to use a list or set, I don't think that will work.
I've also tried looking up algorithms for autocomplete functions, but the ones that I've found seem extremely complicated for what I'm trying to accomplish here.
I also was thinking of using strncmp() to compare the current sequence to a word from the dictionary set, but again, I don't know how exactly that would function in this situation, if at all.
Is it worth it to continue investigating how this would work in a set or should I just try using a sorted list to store my dictionary?


Answer:
Is it worth it to continue investigating how this would work in a set
Yes. In particular, investigate std::set<>::lower_bound()
http://cplusplus.com/reference/stl/set/lower_bound/
std::string closest_match_on_prefix( const std::set<std::string>& set, const std::string& prefix )
{
    std::set<std::string>::const_iterator iterator = set.lower_bound(prefix) ;
    if(iterator == set.end())/* no match */ return "";
    else if(*iterator == prefix)/* exact match */ return *iterator ; }
    else
    {
        // check for prefix match
        const std::string& candidate = *iterator ;
        if(candidate.size() > prefix.size() && candidate.substr(0, prefix.size()) == prefix)
        { /* found closest match */ return candidate ;}
        else { /* no match */ return "" ; } ;
    }
}

That's exactly what I needed! Thanks for your help!