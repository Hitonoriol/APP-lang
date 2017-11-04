<h1> APP-lang</h1>
<h3>One-symbol esoteric programming language interpreter</h3>
Operators:
<pre>
<table>
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
    <td>Writes current int cell value if current mode is 0 and writes current string cell value if mode is 1</td> 
  </tr>
  <tr>
    <td>_</td>
    <td>Echoes end of line</td> 
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
    <td>If MODE is 0, gets int from keyboard to int cell, if MODE is 1, gets string from keyboard.</td> 
  </tr>
  <tr>
    <td>+</td>
    <td>Sets value of current cell to sum of two previous cells (cell[current] = cell[DATA0] + cell[DATA1])</td> 
  </tr>
  <tr>
    <td>-</td>
    <td>Sets value of current cell to cell[DATA0] - cell[DATA1]</td> 
  </tr>
  <tr>
    <td>?</td>
    <td>If cell[DATA0] == cell[DATA1], sets current cell to 1, otherwise, to 0.</td> 
  </tr>
   <tr>
    <td>g</td>
    <td>If cell[DATA0] > cell[DATA1], sets current cell to 1, otherwise, to 0.</td> 
  </tr>
   <tr>
    <td>s</td>
    <td>If cell[DATA0] < cell[DATA1], sets current cell to 1, otherwise, to 0.</td> 
  </tr>
   <tr>
    <td>r</td>
    <td>Sets current cell value to random int in range min = cell[DATA0] & max = cell[DATA1]</td> 
  </tr>
  <tr>
    <td>{</td>
    <td>Repeats 1 operator after it cell[DATA0] times</td> 
  </tr>
  <tr>
    <td>!</td>
    <td>Executes next operator if cell[DATA0] == 1</td> 
  </tr>
  <tr>
    <td>c</td>
    <td>Prints current cell number</td> 
  </tr>
  <tr>
    <td>S</td>
    <td>Switches MODE between 0 (int) and 1 (string)</td> 
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
    <td>G</td>
    <td>Jumps to OP with number of current cell value, i.e. code xGxxw will write 10 on screen</td> 
  </tr>
  <tr>
    <td>C</td>
    <td>Copies current cell number to cell with number of previous cell value. Works with string cells as well as with int</td> 
  </tr>
  <tr>
    <td>@</td>
    <td>Unar minus to current cell</td> 
  </tr>
</table>
</pre>
