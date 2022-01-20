Simulates an ocean growing over time, represented by a growing 2d array of many seas. 
Each sea contains many blocks with an integer number to represent how many fish are in that block (M if more than 10).
Over time with each step, sharks and fish continue to populate those seas, with both of them having a chance to reproduce.
Sharks also will eat fish to replenish their hunger, and will die if they become too hungry.
Both sharks and fish can die naturally once they reach a certain age.
They can also expand to new seas and create new seas once they enter an area beyond their current sea.
The simulation ends once the amount of seas exceeds the limit of 8.
An example output is shown in the text file sample_output.txt.
