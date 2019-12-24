<h1> APP-lang</h1>
<h3>One-symbol esoteric programming language interpreter</h3>

# Command line args

Execute APP source file:

`app <filename>`

Interactive mode:

`app`

# Operators:
<pre>
<table style="table-layout: fixed; width: 100%;word-wrap: normal;">
  <tr>
    <th>Operator</th>
    <th>Description</th> 
  </tr>
  <tr>
    <td>a</td>
    <td>Set current int cell to 0 if MODE is 0 // if MODE is 1, clear current string cell</td> 
  </tr>
  <tr>
    <td>p</td>
    <td>Increment current cell</td> 
  </tr>
  
  <tr>
    <td>m</td>
    <td>Decrement current cell</td> 
  </tr>
  <tr>
    <td>w</td>
    <td>Write current number cell value with float-point precision from DATA5 cell (3 digits by default) to buffer cell (DATA7) if current mode is 0 // write current string cell value to buffer cell if mode is 1</td> 
  </tr>
   <tr>
    <td>W</td>
    <td>Print buffer cell value on the screen, then clear it</td> 
  </tr>
   <tr>
    <td>P</td>
    <td>Clear the buffer cell</td> 
  </tr>
  <tr>
    <td>_</td>
    <td>Console line break</td> 
  </tr>
  <tr>
    <td>&gt;</td>
    <td>Next cell</td> 
  </tr>
  <tr>
    <td>&lt;</td>
    <td>Previous cell</td> 
  </tr>
  <tr>
    <td>.</td>
    <td>Put a character with code from current int cell to current string cell</td> 
  </tr>
  <tr>
    <td>v</td>
    <td>Add 5 to current cell</td> 
  </tr>
  <tr>
    <td>x</td>
    <td>Add 10 to current cell</td> 
  </tr>
  <tr>
    <td>i</td>
    <td>If MODE is 0, get int from keyboard to number cell // if MODE is 1, get string from keyboard.</td> 
  </tr>
  <tr>
    <td>+</td>
    <td>if MODE is 0, set value of current cell to cell[DATA0] + cell[DATA1], // if MODE is 1, join DATA0 and DATA1 strings and put result to current string cell</td> 
  </tr>
  <tr>
    <td>-</td>
    <td>Set value of current cell to cell[DATA0] - cell[DATA1]</td> 
  </tr>
  <tr>
    <td>?</td>
    <td>If cell[DATA0] == cell[DATA1], set cell[DATA2] to 1, otherwise, to 0. Works with int cells as well as with strings.</td> 
  </tr>
   <tr>
    <td>g</td>
    <td>If cell[DATA0] > cell[DATA1], set cell[DATA2] to 1, otherwise, to 0.</td> 
  </tr>
   <tr>
    <td>s</td>
    <td>If cell[DATA0] < cell[DATA1], set cell[DATA2] to 1, otherwise, to 0.</td> 
  </tr>
   <tr>
    <td>r</td>
    <td>Set current cell value to random int in range min = cell[DATA0] & max = cell[DATA1]</td> 
  </tr>
  <tr>
    <td>{...}</td>
    <td>Repeat operators between "{" and "}" cell[DATA3] times</td> 
  </tr>
  <tr>
    <td>!...;</td>
    <td>Execute operators between "!" and ";" if cell[DATA2] == 1</td> 
  </tr>
  <tr>
    <td>c</td>
    <td>Put current cell number to current int cell</td> 
  </tr>
  <tr>
    <td>S</td>
    <td>Switch MODE between 0 (numbers) and 1 (string)</td> 
  </tr>
  <tr>
    <td>/</td>
    <td>Make cell[current] = cell[DATA0] / cell[DATA1]</td> 
  </tr>
  <tr>
    <td>*</td>
    <td>Make cell[current] = cell[DATA0] * cell[DATA1]</td> 
  </tr>
  <tr>
    <td>j</td>
    <td>Jump to memory cell which number is stored in DATA4 cell. Default DATA4 value is its own position, so to set cell number to jump you have to do something like that: "jxjR" - this code will make APP jump to 10th memory cell and then back to DATA4</td> 
  </tr>
<tr>
    <td>R</td>
    <td>Return from cell jump (works only after "j")</td> 
  </tr>
  <tr>
    <td>C</td>
    <td>Copy current cell number to cell with number from DATA6. Works with string cells as well as with int</td> 
  </tr>
  <tr>
    <td>@</td>
    <td>Current cell *= -1</td> 
  </tr>
  <tr>
    <td>P</td>
    <td>Put current string cell to a file with name from DATA0 string cell</td> 
  </tr>
  <tr>
    <td>l</td>
    <td>Load string to current string cell from file with name from DATA0 string cell</td> 
  </tr>
  <tr>
    <td>&</td>
    <td>Append current number cell value to current string cell if mode is 0, // if mode is 1, convert current string cell value to current number cell</td> 
  </tr>
  <tr>
    <td>A</td>
    <td>Put substring from string DATA0 with start DATA0 and length DATA1 to destination string cell</td> 
  </tr>
   <tr>
    <td>b</td>
    <td>Put current string cell length to current number cell</td> 
  </tr>
   <tr>
    <td>q</td>
    <td>Put the position of the first occurance of substring DATA1 in string DATA0 to destination cell</td> 
  </tr>
   <tr>
    <td>Q</td>
    <td>Erase substring DATA1 from string DATA0 and put the result to destination string cell</td> 
  </tr>
   <tr>
    <td>e</td>
    <td>Execute APP code from String[Int[DATA0]]</td> 
  </tr>
   <tr>
    <td>D</td>
    <td>Set current cell as destination</td> 
  </tr>
     <tr>
    <td>0</td>
    <td>Set current cell as DATA0</td> 
  </tr>
     <tr>
    <td>1</td>
    <td>Set current cell as DATA1</td> 
  </tr>
<tr>
    <td>2</td>
    <td>Set current cell as DATA2</td> 
  </tr>
<tr>
    <td>3</td>
    <td>Set current cell as DATA3</td> 
  </tr>
     <tr>
    <td>z</td>
    <td>Push current cell's value to stack (two different stacks for int and string cells | mode0 -> int; mode1 -> string)</td> 
  </tr>
     <tr>
    <td>Z</td>
    <td>Pop the top value from stack to current cell (mode0 -> int; mode1 -> string)</td> 
  </tr>
     <tr>
    <td>E</td>
    <td>Put length of stack to current cell (mode0 -> length of int stack; mode1 -> length  of string stack)</td> 
  </tr>
<tr>
    <td>[mode_num]</td>
    <td>Set MODE to 0.</td> 
</tr>
<tr>
    <td>[mode_str]</td>
    <td>Set MODE to 1.</td> 
</tr>
<tr>
    <td>[*8=var_name]</td>
    <td>Create alias 'var_name' for data cell #8.</td> 
</tr>
<tr>
    <td>[$var_name=%ppwW]</td>
    <td>Run specified code with origin point in cell with alias var_name</td> 
</tr>
<tr>
    <td>[$var_name=123]</td>
    <td>Set value of var_name to 123</td> 
</tr>
<tr>
    <td>[>var_name]</td>
    <td>Set cell with alias 'var_name' as current</td> 
</tr>
<tr>
    <td>[$5=10]</td>
    <td>Set 5th Int cell's value to 10</td> 
  </tr>
<tr>
    <td>[$5=$10]</td>
    <td>Set 5th Int cell's value to 10th cell value</td> 
  </tr>
<tr>
    <td>[$5=#10]</td>
    <td>Temporarily set current cell to 5th and execute APP code from 10th string cell</td> 
  </tr>
<tr>
    <td>[$5=%ppwW]</td>
    <td>Run operators in 5th cell</td> 
  </tr>
<tr>
    <td>[$c=10] / [$c=$10] / [$c=%app] / [$10=$c]</td>
    <td>c -- current cell</td> 
  </tr>
  <tr>
    <td>[e]</td>
    <td>Skip next goto</td> 
  </tr>
<tr>
    <td>[:label]</td>
    <td>Declare a label (any name except ([,],/,\,") )</td> 
  </tr>
<tr>
    <td>[#label]</td>
    <td>Go to label. Don't write ":" here. Just don't.</td> 
  </tr>
  <tr>
    <td>[ret]</td>
    <td>Return to last goto</td> 
  </tr>
  <tr>
    <td>[!12345]</td>
    <td>Sets current cell to a value</td> 
  </tr>
  <tr>
    <td>[>5]</td>
    <td>Jumps to a memory cell</td> 
  </tr>
  
</table>
</pre>
