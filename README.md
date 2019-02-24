<h1> APP-lang</h1>
<h3>One-symbol esoteric programming language interpreter</h3>
Operators:
<pre>
<table style="table-layout: fixed; width: 100%;word-wrap: normal;">
  <tr>
    <th>Operator</th>
    <th>Description</th> 
  </tr>
  <tr>
    <td>a</td>
    <td>Sets current int cell to 0 if MODE is 0 and if MODE is 1, clears current string cell</td> 
  </tr>
  <tr>
    <td>p</td>
    <td>Increments current cell</td> 
  </tr>
  
  <tr>
    <td>m</td>
    <td>Decrements current cell</td> 
  </tr>
  <tr>
    <td>w</td>
    <td>Writes current number cell value with float-point precision from DATA5 cell (3 by default) to buffer cell (DATA7) if current mode is 0 and writes current string cell value to buffer cell if mode is 1</td> 
  </tr>
   <tr>
    <td>W</td>
    <td>Prints buffer cell value on the screen</td> 
  </tr>
   <tr>
    <td>P</td>
    <td>Clears the buffer cell</td> 
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
    <td>Puts a symbol with code from current int cell to current string cell</td> 
  </tr>
  <tr>
    <td>v</td>
    <td>Adds 5 to current cell</td> 
  </tr>
  <tr>
    <td>x</td>
    <td>Adds 10 to current cell</td> 
  </tr>
  <tr>
    <td>i</td>
    <td>If MODE is 0, gets int(!) from keyboard to number cell, if MODE is 1, gets string from keyboard.</td> 
  </tr>
  <tr>
    <td>+</td>
    <td>if MODE is 0, sets value of current cell to cell[DATA0] + cell[DATA1], otherwise, joins DATA0 and DATA1 strings to current cell string</td> 
  </tr>
  <tr>
    <td>-</td>
    <td>Sets value of current cell to cell[DATA0] - cell[DATA1]</td> 
  </tr>
  <tr>
    <td>?</td>
    <td>If cell[DATA0] == cell[DATA1], sets cell[DATA2] to 1, otherwise, to 0.</td> 
  </tr>
   <tr>
    <td>g</td>
    <td>If cell[DATA0] > cell[DATA1], sets cell[DATA2] to 1, otherwise, to 0.</td> 
  </tr>
   <tr>
    <td>s</td>
    <td>If cell[DATA0] < cell[DATA1], sets cell[DATA2] to 1, otherwise, to 0.</td> 
  </tr>
   <tr>
    <td>r</td>
    <td>Sets current cell value to random int in range min = cell[DATA0] & max = cell[DATA1]</td> 
  </tr>
  <tr>
    <td>{...}</td>
    <td>Repeats operators between "{" and "}" cell[DATA3] times</td> 
  </tr>
  <tr>
    <td>!...;</td>
    <td>Executes next operator if cell[DATA2] == 1</td> 
  </tr>
  <tr>
    <td>c</td>
    <td>Puts current cell number to current int cell</td> 
  </tr>
  <tr>
    <td>S</td>
    <td>Switches MODE between 0 (numbers) and 1 (string)</td> 
  </tr>
  <tr>
    <td>/</td>
    <td>Makes cell[current] = cell[DATA0] / cell[DATA1]</td> 
  </tr>
  <tr>
    <td>*</td>
    <td>Makes cell[current] = cell[DATA0] * cell[DATA1]</td> 
  </tr>
  <tr>
    <td>j</td>
    <td>Jumps to memory cell which number is stored in DATA4 cell. Default DATA4 value is its own number, so to set cell number to jump you have to do something like that: "jxjR" - this code will make APP jump to 10th memory cell and then back to DATA4</td> 
  </tr>
<tr>
    <td>R</td>
    <td>Return from cell jump (works only after "j")</td> 
  </tr>
  <tr>
    <td>C</td>
    <td>Copies current cell number to cell with number from DATA6. Works with string cells as well as with int</td> 
  </tr>
  <tr>
    <td>@</td>
    <td>Unary minus to current cell (yep, that's important)</td> 
  </tr>
  <tr>
    <td>P</td>
    <td>Puts current string cell to a file with name from DATA0 string cell</td> 
  </tr>
  <tr>
    <td>l</td>
    <td>Loads string to current string cell from file with name from DATA0 string cell</td> 
  </tr>
  <tr>
    <td>&</td>
    <td>Appends current number cell value to current string cell if mode is 0, and if mode is 1, converts current string cell value to current number cell</td> 
  </tr>
  <tr>
    <td>A</td>
    <td>Puts substring from string DATA0 with start DATA0 and length DATA1 to destination string cell</td> 
  </tr>
   <tr>
    <td>b</td>
    <td>Puts current string cell length to current number cell</td> 
  </tr>
   <tr>
    <td>q</td>
    <td>Returns the position of the first occurance of substring DATA1 in string DATA0 to destination cell</td> 
  </tr>
   <tr>
    <td>Q</td>
    <td>Erases substring DATA1 from string DATA0 and puts the result to destination string cell</td> 
  </tr>
   <tr>
    <td>e</td>
    <td>Execute APP code from String[Int[DATA0]]</td> 
  </tr>
   <tr>
    <td>D</td>
    <td>Sets destination to current cell</td> 
  </tr>
     <tr>
    <td>0</td>
    <td>Sets DATA0 to current cell's address</td> 
  </tr>
     <tr>
    <td>1</td>
    <td>Set DATA1 to current cell's address</td> 
  </tr>
<tr>
    <td>2</td>
    <td>Set DATA2 to current cell's address</td> 
  </tr>
<tr>
    <td>3</td>
    <td>Set DATA3 to current cell's address</td> 
  </tr>
     <tr>
    <td>z</td>
    <td>Pushes current cell's value to stack (two different stacks for int and string cells | mode0 -> int; mode1 -> string)</td> 
  </tr>
     <tr>
    <td>Z</td>
    <td>Pops the top value from stack to current cell (mode0 -> int; mode1 -> string)</td> 
  </tr>
     <tr>
    <td>E</td>
    <td>Puts length of stack to Int[CURRENT] (mode0 -> length of int stack; mode1 -> length  of string stack)</td> 
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
