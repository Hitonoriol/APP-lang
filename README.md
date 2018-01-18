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
    <td>Writes current number cell value with float-point precision from DATA5 cell (3 by default) if current mode is 0 and writes current string cell value if mode is 1</td> 
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
    <td>Sets value of current cell to cell[DATA0] + cell[DATA1]</td> 
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
    <td>{</td>
    <td>Repeats 1 operator after it cell[DATA3] times</td> 
  </tr>
  <tr>
    <td>!</td>
    <td>Executes next operator if cell[DATA2] == 1</td> 
  </tr>
  <tr>
    <td>c</td>
    <td>Prints current cell number</td> 
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
    <td>R</td>
    <td>Makes cell[current] = cell[DATA0] / cell[DATA1]</td> 
  </tr>
  <tr>
    <td>j</td>
    <td>Jumps to memory cell which number is stored in DATA4 cell. Default DATA4 value is its own number, so to set cell number to jump you have to do something like that: "jxjR" - this code will make APP jump to 10th memory cell and then back to DATA4</td> 
  </tr>
<tr>
    <td>R</td>
    <td>Returns to previous cell (works only after "j")</td> 
  </tr>
  <tr>
    <td>C</td>
    <td>Copies current cell number to cell with number of previous cell value. Works with string cells as well as with int</td> 
  </tr>
  <tr>
    <td>@</td>
    <td>Unar minus to current cell</td> 
  </tr>
<tr>
    <td>[:label]</td>
    <td>Declare a label (any name except ([,],/,\,") )</td> 
  </tr>
<tr>
    <td>[#label]</td>
    <td>Go to label. Don't write ":" here. Just don't.</td> 
  </tr>
</table>
</pre>
