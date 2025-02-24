/* Google: Suppose I give you a dictionary of words; the size of the 
 * dictionary is finite. Each word in the dictionary is composed from 
 * a set of characters; the size of the alphabet is finite. 
 * Find the longest word in the dictionary with the property that it 
 * can be built by adding one char at a time and each step is a valid 
 * word in the dictionary.
 * Refer to:
 * http://www.mitbbs.com/article_t1/JobHunting/31995121_0_1.html
 */

// gloomyturkey's java code (can not compile in C++)
// Time complexity: O(n * k), in which n is the number of words,
// k is the average length of words in the dictionary. 
public void find() {
  // Assume that the longest word has 30 chars
  int N = 30; 

  // Read word list file into a vetor of strings
  String content = FileHelper.readFile(DIR + "/WORD.LST");
  String[] words = content.split("\n");

  // word_set: array of hashset, in which all words are sorted by length
  HashSet<String>[] word_set = new HashSet[30];

  // word_map: array of hashmap whose key is word, 
  // value is another word that has one char removed. 
  HashMap<String, String>[] word_map = new HashMap[N];

  // Initialize word_set and word_map
  for (int i = 0; i < N; i++) {
    word_set[i] = new HashSet<String>();
    word_map[i] = new HashMap<String, String>();
  }
  // Populate word_set
  for (String word : words) 
    word_set[word.length()].add(word);
        
  // Populate word_map[1], whose value is empty string
  for (String word : word_set[1]) 
    word_map[1].put(word, "");
          
  // Populate word_map[2], ..., word_map[N-1]
  int i = 2;
  while (i < N) {
    for (String word : word_set[i]) {
      // Remove any char, see whether the new word is valid or not
      for (int j = 0; j < word.length(); j++) {
	String shrink = word.substring(0, j) + word.substring(j + 1);
	// If any valid word that has one less char is found, record it
	// in word_map and stop searching
	if (word_map[i-1].containsKey(shrink)) {
	  map[i].put(word, shrink);
	  break;
	}
      } // end of inner for loop
    } // end of outer for loop

    // If no any word of length i can be composed by 
    // adding one char to a valid word, we are done!
    if (map[i].size() == 0) 
      break;

    // Level i is good, let's go to the next level
    i++;
  }  
  
  // Print out all valid paths, from longest word to the shortest
  String word = map[i-1].keySet().iterator().next();
  for (int j = i - 1; j > 0; j--) {
    System.out.print(word + " - ");
    word = map[j].get(word);
  }
}

// xiaotuzi5 (can not compile)
// ----------------------------------------------------------------------
/* Descriptoin: given a dictionary of words, find the longest word in the 
 * dictionary such that it can be built from successively adding a single 
 * character to an existing word in the dictionary in any location
 * Input: Dict& dict, vector<string> v, vector<string> & result
 * K.O.: back tracking
 */
// Find the valid words in the dictionary that are formed by 
// inserting one char into any position of input string.
vector<string> String::generate_next_string(string& s, String::Dict& dict){
  string t;
  vector<string> v;

  // temp holds new words generated by inserting one char into s.
  // Use std::set to remove duplicates.
  set<string> temp; 
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j <= s.length(); j++){
      t = s;
      t.insert(t.begin() + j,'a' + i);  
      if (dict.find(t) != dict.end())
	temp.insert(t);
    }
  }

  // Copy new words into v
  set<string>::iterator j;
  for (j = temp.begin(); j != temp.end(); j++)
    v.push_back(*j);

  return v;  
}

// Recursive helper function:
// v is a vector of words of equal length; result has all the valid 
// words that are formed by adding one char into a valid word.
void String::find_largest_word_rec(Dict& dict, vector<string> v, 
				   vector<string> & result)
{
  // count keeps track of the number of words in v that can not
  // generate any valid word by inserting one char into it.
  unsigned count = 0;

  for(size_t i = 0; i < v.size(); i++) {
    vector<string> t = String::generate_next_string(v[i], dict); 
    if (!t.size()) {
      count++;
      // If no word in v can form any valid word by inserting one char, 
      // the search is done!
      if (count == v.size() - 1) 
	return;
    }

    // If valid words are found, keep searching recursively 
    else {
      for (size_t j = 0; j < t.size(); j++)
	result.push_back(t[j]);
      find_largest_word_rec(dict, t, result);
    }  
  }
}

// Wrapper function:
// dict is the input dictionary that has all valid words;
// v is a vector of words whose length is 1;
// result has all the valid words that are formed by adding 
// one char into a valid word.
string String::find_largest_word(Dict& dict, vector<string> v)
{
  vector<string> result;
  find_largest_word_rec(dict,v,result);
  
  // sort words in result by length. 
  // The longest word will be ranked before shorter words. 
  sort(result.begin(),result.end(), String::comparelength);

  // The first word in result should be what we are looking for!
  return result[0];
}

// Java code by Datamining (can NOT compile)
// -----------------------------------------------------------
String findLongest(Set<String> dict) {
  String longest = null;
  Set<String> mem = new HashSet<String>();
  for (String word : dict) {
    if (helper(word, mem, dict)) {
      if (longest == null || word.length() > longest.length()) {
	longest = word;
      }
    }
  }
  
  return longest;
}

// Recursive helper function that is called by findLongest().
// word is the input word that will be checked;    
// mem keeps track of words that have been confirmed to have
// a valid path to a single char word; dict is input dictionary.
boolean helper(String word, Set<String> mem, Set<String> dict) {
  if (word == null || word.isEmpty() || !dict.contains(word)) {
    return false;
  }

  if (word.length() == 1) {
    return dict.contains(word);
  }

  if (mem.contains(word)) {
    return true;
  }
        
  for (int i = 0; i < word.length(); ++i) {
    String newWord = word.substring(0, i) + word.substring(i+1);
    boolean isIn = helper(newWord, mem, dict);
    if (isIn) {
      mem.add(word);
      return true;
    }
  }
  return false;
}
