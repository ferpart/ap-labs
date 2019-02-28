# Lab 2.3 - Cross-referencer

For the for the following lab we were assigned the next instructions:

Write a cross-referencer in C that prints a list of all words in a document, and
, for each word, a list of the line numbers on which it occurs. Remove noise 
words like `the`, `and`, and so on.

The noise words that were chosen have been taken from the following code at 
[Yoast's gitHub page](https://github.com/Yoast/YoastSEO.js/blob/develop/src/config/stopwords.js "YoastSEO.js")

The following is a javascript script with said stop words:

```javascript
/** @module config/stopwords */

/**
 * Returns an array with stopwords to be used by the analyzer.
 *
 * @returns {Array} stopwords The array filled with stopwords.
 */
export default function() {
	return [ "a", "about", "above", "after", "again", "against", "all", 
		 "am", "an", "and", "any", "are", "as", "at", "be", "because", 
		 "been", "before", "being", "below", "between", "both", "but", 
		 "by", "could", "did", "do", "does", "doing", "down", "during", 
		 "each", "few", "for", "from", "further", "had", "has", "have", 
		 "having", "he", "he'd", "he'll", "he's", "her", "here", 
		 "here's", "hers", "herself", "him", "himself", "his", "how", 
		 "how's", "i", "i'd", "i'll", "i'm", "i've", "if", "in", "into", 
		 "is", "it", "it's", "its", "itself", "let's", "me", "more", 
		 "most", "my", "myself", "nor", "of", "on", "once", "only", 
		 "or", "other", "ought", "our", "ours", "ourselves", "out", 
		 "over", "own", "same", "she", "she'd", "she'll", "she's", 
		 "should", "so", "some", "such", "than", "that", "that's", 
		 "the", "their", "theirs", "them", "themselves", "then", 
		 "there", "there's", "these", "they", "they'd", "they'll", 
		 "they're", "they've", "this", "those", "through", "to", "too", 
		 "under", "until", "up", "very", "was", "we", "we'd", "we'll", 
		 "we're", "we've", "were", "what", "what's", "when", "when's", 
		 "where", "where's", "which", "while", "who", "who's", "whom", 
		 "why", "why's", "with", "would", "you", "you'd", "you'll", 
		 "you're", "you've", "your", "yours", "yourself", "yourselves" 
		];
};
```




```
./cross-ref document.txt
```

General Requirements and Considerations
---------------------------------------
- Use the `cross-ref.c` file for your implementation.
- Update `README.md` with the proper steps for building and running your code.
- Follow the command-line arguments convention.
- Don't forget to handle errors properly.
- Coding best practices implementation will be also considered.

Test cases
----------
Your program will be tested with the following txt-based books.

- [irving-little-573.txt](./irving-little-573.txt)
- [irving-london-598.txt](./irving-london-598.txt)

## How to run

To run this c program the user only needs to do the following.

```
make

./cross-ref document.txt
```

A list of all words, and their appearances (shown with line numbers) will be
printed. 
