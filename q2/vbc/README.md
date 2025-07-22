vbc = Very Basic Calculator

The method to solve this task is called Recursive descent parsing.

Recursive descent parsing is a popular technique for implementing parsers for programming languages or data formats. It’s based on writing a set of functions (one per grammar rule) that “descend” recursively through the structure of the input, following the grammar of the language being parsed.

Top-down parsing: It starts from the start symbol (usually the root of the grammar) and tries to match the input tokens by calling functions corresponding to each non-terminal in the grammar.

Each function: Implements a rule of the grammar. These functions call each other recursively as needed.

Backtracking: Basic recursive descent parsers may backtrack when a choice fails, but more robust versions use lookahead (peeking at upcoming tokens) to avoid unnecessary backtracking.

Expr   → Term ((‘+’ | ‘-’) Term)*
Term   → Factor ((‘*’ | ‘/’) Factor)*
Factor → NUMBER | ‘(’ Expr ‘)’

1. accept (or “match,” “consume,” etc.)

Purpose: To optionally consume a specific token or character if it’s present, and advance the parser’s position.

Why: This pattern is super common in grammar parsing, for optional symbols, or to advance past known punctuation.

Variants: You might also see match, consume, or even peek_and_advance functions.


2. unexpected (or “syntax_error,” etc.)

Purpose: To handle the case where the parser encounters an unexpected token or end of input, often printing an error message and/or aborting parsing.

Why: Detecting and reporting syntax errors in a clear way is essential for any parser.

Variants: Some call it syntax_error, parse_error, or just print directly inside parsing functions.
