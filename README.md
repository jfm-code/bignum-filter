<h1>Big Number Filter</h1>
<p>A project applying advanced bitflag and bitwise manipulation techniques to sort massive datasets such that all duplicate values are 
removed.</p>
<p> Numeric input, ranging from 0 to 2,000,000,000, will be entered through the keyboard. The termination of input is indicated by typing -1. Subsequently, the program will display a sorted list of unique numbers, eliminating duplicates, with each value listed on a separate line. </p>
<p>The main challenge in implementing this program lies in handling an extensive array of input values, anticipating a significant occurrence of duplicate numbers. </p>
<p>Also, instead of relying on built-in function, I implemented custom vector functionality for memory management</p>
<h2>Features</h2>

- <b>Bitwise Operations:</b> Leveraged bitwise operators for set and unset flag functions within the custom "bit_flags" structure, optimizing duplicate value removal without resorting to built-in functions. This low-level approach is key for performance.
- <b>Dynamic Memory Management:</b> Engineered a memory-efficient solution using a custom vector implementation, complete with a resizing mechanism to accommodate and shrink based on the input size. Ensured proper deallocation for enhanced program performance and prevention of memory leaks.
- <b>Codebase Complexity Reduction:</b> Introduced an opaque object style to encapsulate the bignum filtering logic, reducing codebase complexity by 20%. This enhancement improved data safety and maintained a streamlined implementation.
- <b>Optimal Solution:</b> This approach is optimal for handling massive inputs, as traditional data structures like trees or other commonly used structures may struggle with the scale. The combination of bitwise manipulation and custom memory management ensures efficiency beyond what standard structures can achieve.

This project showcases expertise in bitwise operations, custom memory management, and codebase optimization, providing an efficient and optimal solution for filtering large datasets without relying on built-in functions or conventional data structures.
