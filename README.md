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
    <td>Copies current cell number to cell with number from DATA6. Works with string cells as well as with int</td> 
  </tr>
  <tr>
    <td>@</td>
    <td>Unar minus to current cell</td> 
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
    <td>Puts substring with start position from DATA0 and length from DATA1 from previous string cell to current</td> 
  </tr>
   <tr>
    <td>b</td>
    <td>Puts current string cell length to current number cell</td> 
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
    <td>[!12345]</td>
    <td>Sets current cell to a value</td> 
  </tr>
  <tr>
    <td>[>5]</td>
    <td>Jumps to a memory cell</td> 
  </tr>
  
</table>
</pre>
