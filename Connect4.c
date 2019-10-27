#include <stdio.h> 

#include <ctype.h> //To Make Sure The User Enters A Number --- Not In Use Yet.../Couldn't Figure It Out 

 

#define ANSI_COLOR_YELLOW "\x1b[33m" //COLORSSSSSSS 

#define ANSI_COLOR_RESET   "\x1b[0m" //UNDO COLORSSSSSSS 

#define ANSI_COLOR_RED     "\x1b[31m"//MORE COLORSSSSSSS --- Not Working Yet 

#define ANSI_COLOR_CYAN    "\x1b[36m"//EVEN MORE COLORSSSSSSS --- Not Working Yet  

 

//Function Prototype List!

 

void DisplayBoard(char Board[], int Counter); //Shows The Board 

int Placement(int x); //Asks The Player For A Placement 

int LegalMove (int Place, char Board[]); //Puts A Chip Where The User Placed It 

void Switcher(int Counter); //Switches Which Players Turn It Is 

int MoveMaker(int Place, char Board[], int Counter, int Legal); //Function That Makes Move 

int VerticalChecker(char Board[], int Legal, int Win); //Function That Checks If The Player Won Vertically 

int HorizontalChecker(char Board[], int Legal, int WinH); //Function That Checks If The Player Won Horizontally 

int GameWon(char Board[], int Legal, int Place, int WinH, int WinV, int WinDT, int WinDB, int WinD, int Win); //Function That Checks If The Player Won  

int TopDiagonalChecker(char Board[], int Legal, int WinD); //Function That Checks If The Player Won Diagonally 

int Menu(int Input); //Brings Player To Main Menu 

int ReadGame(char Board[], int Counter, int Command, int H); //Function That Checks Saved Game 

int WriteGame(int G, char Board[], int Counter); //Function That Writes The Current Game To A File For Saving  

int BottomDiagonalChecker(char Board[], int Legal, int WinDB); //Function That Checks If The Player Won Diagonally From Bottom 

int DiagonalChecker(char Board[], int Legal, int Place, int WinD); 

 

int main(void) //Main Function Where All The Functions Run 

{ 

//Variable List + File 

 

 

 

int H =0; //Value To Run For Loop In Retriving Data From Saved File 

int G = 0; //Value To Run For Loop In File Saving Operations 

int Save = 0; //Value That Determines Whether To Save The Game Or Not 

int Input = 0; //General Variable To Get Menu Function To Run 

int Command = 0; //Value That Menu Returns That Determines The Course Of The Game 

int y = 1; //General Variable To Get Things To Run 

int Place = 0; //User Entered Value That Holds The Column The User Wants To Place The Chip In 

char Board[42]; //Creates A Board With 42 Slots 

int i; //Variable To Make For Loop For The Clean Board To Run 

 

 for (i = 0; i <= 41; i++) //Sets The Board To All Empty Spots 

    { 

        Board[i] = ' '; //Puts Spaces For Each Board Value 

    } 

 

int Counter = 0; //Counter For Switcher Function To Track and Choose Which Player It Is 

int Legal = 0; //Value LegalMove Function Returns And Determines Message Returned In MoveMaker 

int WinH = 0; //Value The Horizontal Win Checker Returns  

int WinV = 0; //Value The Vertical Win Checker Returns 

int WinDT = 0; //Value The Diagonal Win Checker Returns From Top 

int WinDB = 0; //Value The Diagonal Win Checker Returns From Bottom 

int Win = 0; //Value That Checks If A Player Won And Triggers The End Of The Game 

int Winner = 0; //Value That GameWon Function Stores Value In 

int WinD = 0; 

 

//Start Of Game 

 

while (Command != 27 && Command != 100) //Pops Out Of Loop When Command Is 27 (Starts New Game) Or 100 (Loads Saved Game) 

{ 

Command = Menu(Input); //Asks Player What They Want To Do  

 

if(Command == 1)  

{ 

return(0); //To End Game If User Chooses To Exit 

} 

if (Command == 20) //If The Player Wants To Load A Saved Game 

{ 

Command = ReadGame(Board, Counter, Command, H); 

} 

} 

 

if (Command == 27) 

{ 

printf("You Have Started A New Game!"); //If User Starts A New Game 

} 

if (Command == 100) 

{ 

printf("You Have Loaded A Saved Game!"); //If User Loads A Old Game 

} 

 

printf("\nWelcome to Connect 4!\n"); //Happy Intro Is Important 

printf("\n 1 2 3 4 5 6 7 \n"); 

 

    for (i = 0; i <= 5; i++) //Prints First Board Without Any Chips 

    { 

        printf(ANSI_COLOR_CYAN "|%c|%c|%c|%c|%c|%c|%c|\n" ANSI_COLOR_RESET, Board[7*i],  

Board[7*i+1], Board[7*i+2], Board[7*i+3], Board[7*i+4], 

Board[7*i+5], Board[7*i+6]); //All Blue Board  

} 

 

do  

{ 

 

Switcher(Counter); //Switches Which Player's Turn It Is 

Place = Placement(y);//Storing The Move Into Place 

 

printf("You Picked The Column: %d\n", Place); //Tells The User What Column They Picked 

printf("\n"); 

 

Legal = LegalMove(Place, Board); //Decides Whether The Move Is Legal 

Counter = MoveMaker(Place, Board, Counter, Legal); //Updates The Board With New Chip If Move Is Legal 

 

printf("\nThe Board Is:"); 

printf("\n"); 

DisplayBoard(Board, Counter); //Shows The New Board After Move Is Made  

 

Winner = GameWon(Board, Legal, Place, WinH, WinV, WinDT, WinDB, WinD, Win); //Checks Whether A Player Won And Stores A Value In Winner 

 

 

if (Winner > 0) //Winner Is The Total Of WinV, WinD, and WinH, So If Either Are Not 0 They Give Winner A Non-Zero Value And Ends The Game 

{ 

printf("\nYou Win!!! "); 

Counter = 44; //Sets The Counter To 44 Forcing It Out Of The While Loop 

printf("Game Over!!! \n"); 

} 

 

Counter++; 

 

if(Counter != 45) //If The Game Was Won, You Can't Save 

{ 


scanf("%d", &Save); //Stores The Number For Save 

} 

 

if(Save == 25) //If Save Command Is Given, Writes A File 

{ 

WriteGame(G, Board, Counter); 

 

return(0); 

} 

 

} while (Counter < 42); 

 

if (Counter == 45) //If The Game Was Won It Reads This Message 

{ 

printf("\nThanks For Playing! ~Garret A :P\n"); 

} 

if (Counter == 42) //If The Game Ended Naturally It Reads This Message  

{ 

printf("\nIt's A Draw! Game Over!\n"); 

printf("\nThanks For Playing! ~Garret A :P\n"); 

} 

 

return(0); 

} 

 

 

//Function List  

 

void DisplayBoard(char Board[], int Counter) //Presents A Board With Chips That Gets Updated 

{ 

    int i; 

     

printf("\n 1 2 3 4 5 6 7 \n"); //Prints The Column Numbers 

 

    for (i = 0; i <= 5; i++) 

    { 

printf(ANSI_COLOR_CYAN "|%c|%c|%c|%c|%c|%c|%c|\n" ANSI_COLOR_RESET, Board[7*i],  

Board[7*i+1], Board[7*i+2], Board[7*i+3], Board[7*i+4], 

Board[7*i+5], Board[7*i+6]); //Prints The Board In Colors Each Time 

} 

    printf("\n"); 
    printf("Enter 25 to save the game or a random number to move to the next turn: ");

} 

 

 

int Placement(int x)   //Function Asks The User For A Column 

{ 

    int Place = 1; 

    printf("Please Enter The Number Of A Column To Place Your Chip In It: "); //Asks For User To Place Chip 

    scanf("%d", &Place); 

 

if (Place <= 0 || Place >= 8) //If The User Enters A Unreal Column Number They Are Thrown Into A Loop Until They Enter A Real Column 

{ 

while (Place <= 0 || Place >= 8) 

{ 

printf("Error, You Picked A Unreal Column!\n"); 

printf("Please Enter The Number Of A Column To Place Your Chip In It: \n"); 

scanf("%d", &Place); 

}     

} 

 

return(Place); 

} 

 

 

int LegalMove (int Place, char Board[]) //Function Places An R Or Y Where The User Picked And Checks If There Is A Chip There 

{ 

     

    int n;  

 

     

    n = 35 + (Place - 1);  

     

    while (Board[n] == 'R' || Board[n] == 'Y') 

    { 

        n = n - 7; //If There Is A Chip There It Checks The Space Above 

    } 

 

if (n < 0 || n > 41) 

{ 

return(45); //If N Ends Up Below 0 Or Above 42 Gives 45 

} 

else 

{ 

return(n); 

} 

}    

 

int MoveMaker(int Place, char Board[], int Counter, int Legal) //Makes The Move If It Passes The Legal Counter 

{ 

if (Legal == 45) 

{ 

printf("Error, That Column Is Full!"); //If Given 45, It Asks The User To Enter A Different Column 

printf("\nTry Again!\n"); 

Counter = Counter - 1;  

return(Counter); 

} 

 

if (Counter%2 == 0) 

{ 

    Board[Legal] = 'R'; //If It Is Red Player's Turn It Prints A R 

} 

else 

{  

Board[Legal] = 'Y';//If It Is Yellow Player's Turn It Prints A Y 

} 

 

return(Counter); 

} 

 

 

void Switcher(int Counter) //Switches Which Players Turn It Is 

{ 

if (Counter%2 == 0) //If Even Turn It Is Red Players Turn 

{ 

printf("Red Player It Is Your Turn!\n"); 

printf("\n"); 

} 

else //If Odd Turn It IS Yellow Players Turn 

{ 

printf("Yellow Player, It Is Your Turn!\n"); 

printf("\n"); 

} 

 

} 

 

 

int VerticalChecker(char Board[], int Legal, int WinV) //Checks If The Player Won Vertically By Running Through Rules For Certain Positions On The Board 

{ 

if (Legal == 35 || Legal == 36 || Legal == 37 || Legal == 38 || Legal == 39 || Legal == 40 || Legal == 41) //Creates Rule For Bottom Row  

{// ~Row If The Values Above It Are The Same... 

if(Board[Legal] == Board[Legal - 7] && Board[Legal] == Board[Legal - 14] && Board[Legal] == Board[Legal - 21]) 

{ 

WinV = 1; 

return(WinV); 

} 

else 

{ 

WinV = 0; 

return(WinV); 

} 

} 

if (Legal == 28 || Legal == 29 || Legal == 30 || Legal == 31 || Legal == 32 || Legal == 33 || Legal == 34) //Creates Rule For Second Row From Bottom    

{  // ~Row If The Values Above It Are The Same... 

if(Board[Legal] == Board[Legal - 7] && Board[Legal] == Board[Legal - 14] && Board[Legal] == Board[Legal + 7]) 

{ 

WinV = 1; 

return(WinV); 

} 

else 

{ 

WinV = 0; 

return(WinV); 

} 

} 

if(Legal == 21 || Legal == 22 || Legal == 23 || Legal == 24 || Legal == 25 || Legal == 26 || Legal == 27) //Creates Rule For Third Row From Bottom  

{ 

if(Board[Legal] == Board[Legal - 7] && Board[Legal] == Board[Legal + 14] && Board[Legal] == Board[Legal + 7]) 

{ 

WinV = 1; 

return(WinV); 

} 

else 

{ 

WinV = 0; 

return(WinV); 

} 

} 

if(Legal == 14 || Legal == 15 || Legal == 16 || Legal == 17 || Legal == 18 || Legal == 19 || Legal == 20) //Creates Rule For Fourth Row From Bottom 

{ 

if(Board[Legal] == Board[Legal + 21] && Board[Legal] == Board[Legal + 14] && Board[Legal] == Board[Legal + 7]) 

{ 

WinV = 1; 

return(WinV); 

} 

else 

{ 

WinV = 0; 

return(WinV); 

} 

} 

if(Legal == 7 || Legal == 8 || Legal == 9 || Legal == 10 || Legal == 11 || Legal == 12 || Legal == 13) //Creates Rule For Fifth Row From Bottom  

{ 

if(Board[Legal] == Board[Legal + 21] && Board[Legal] == Board[Legal + 14] && Board[Legal] == Board[Legal + 7]) 

{ 

WinV = 1; 

return(WinV); 

} 

else 

{ 

WinV = 0; 

return(WinV); 

} 

} 

if(Legal == 0 || Legal == 1 || Legal == 2 || Legal == 3 || Legal == 4 || Legal == 5 || Legal == 6) //Creates Rule For Sixth Row From Bottom 

{ 

if(Board[Legal] == Board[Legal + 21] && Board[Legal] == Board[Legal + 14] && Board[Legal] == Board[Legal + 7]) 

{ 

WinV = 1; 

return(WinV); 

} 

else 

{ 

WinV = 0; 

return(WinV); 

} 

} 

 

WinV = 0; //To Get Rid Of Warning Message, Will Never Actually Be Hit 

return(WinV); 

} 

 

 

int HorizontalChecker(char Board[], int Legal, int WinH) //Checks If The Player Won By Horizontally Running Through The Possibilities 

{ 

if(Legal == 0 || Legal == 7 || Legal == 14 || Legal == 21 || Legal == 28 || Legal == 35) //Checks The Left Boarder Values 

{ 

if(Board[Legal] == Board[Legal + 1] && Board[Legal] == Board[Legal + 2] && Board[Legal] == Board[Legal + 3]) 

{ 

WinH = 1; 

return(WinH); 

} 

else 

{ 

WinH = 0; 

return(WinH); 

} 

} 

if(Legal == 6 || Legal == 13 || Legal == 20 || Legal == 27 || Legal == 34 || Legal == 41) //Checks The Right Boarder Values 

{ 

if(Board[Legal] == Board[Legal - 1] && Board[Legal] == Board[Legal - 2] && Board[Legal] == Board[Legal - 3]) 

{ 

WinH = 1; 

return(WinH); 

} 

else 

{ 

WinH = 0; 

return(WinH); 

} 

} 

if(Legal == 1 || Legal == 8 || Legal == 15 || Legal == 22 || Legal == 29 || Legal == 36) //Checks The Second Column From The Left 

{ 

if(Board[Legal] == Board[Legal + 1] && Board[Legal] == Board[Legal + 2] && Board[Legal] == Board[Legal - 1]) 

{ 

WinH = 1; 

return(WinH); 

} 

else if(Board[Legal] == Board[Legal + 1] && Board[Legal] == Board[Legal + 2] && Board[Legal] == Board[Legal + 3]) 

{ 

WinH = 1; 

return(WinH); 

} 

else 

{ 

WinH = 0; 

return(WinH); 

} 

} 

if(Legal == 5 || Legal == 12 || Legal == 19 || Legal == 26 || Legal == 33 || Legal == 40) //Checks The Second Column From The Right 

{ 

if(Board[Legal] == Board[Legal + 1] && Board[Legal] == Board[Legal - 2] && Board[Legal] == Board[Legal - 1]) 

{ 

WinH = 1; 

return(WinH); 

} 

else if(Board[Legal] == Board[Legal - 1] && Board[Legal] == Board[Legal - 2] && Board[Legal] == Board[Legal - 3]) 

{ 

WinH = 1; 

return(WinH); 

} 

else 

{ 

WinH = 0; 

return(WinH); 

} 

} 

if(Legal == 2 || Legal == 9 || Legal == 16 || Legal == 23 || Legal == 30 || Legal == 37) //Checks The Third Column From The Left 

{ 

if(Board[Legal] == Board[Legal + 1] && Board[Legal] == Board[Legal + 2] && Board[Legal] == Board[Legal - 1]) 

{ 

WinH = 1; 

return(WinH); 

} 

else if(Board[Legal] == Board[Legal + 1] && Board[Legal] == Board[Legal - 2] && Board[Legal] == Board[Legal - 1]) 

{ 

WinH = 1; 

return(WinH); 

} 

else if(Board[Legal] == Board[Legal + 1] && Board[Legal] == Board[Legal + 2] && Board[Legal] == Board[Legal + 3]) 

{ 

WinH = 1; 

return(WinH); 

} 

else  

{ 

WinH = 0; 

return(WinH); 

} 

} 

if(Legal == 4 || Legal == 11 || Legal == 18 || Legal == 25 || Legal == 32 || Legal == 39) //Checks The Third Column From The Right 

{ 

if(Board[Legal] == Board[Legal + 1] && Board[Legal] == Board[Legal + 2] && Board[Legal] == Board[Legal - 1]) 

{ 

WinH = 1; 

return(WinH); 

} 

else if(Board[Legal] == Board[Legal + 1] && Board[Legal] == Board[Legal - 2] && Board[Legal] == Board[Legal - 1]) 

{ 

WinH = 1; 

return(WinH); 

} 

else if(Board[Legal] == Board[Legal - 1] && Board[Legal] == Board[Legal - 2] && Board[Legal] == Board[Legal - 3]) 

{ 

WinH = 1; 

return(WinH); 

} 

else  

{ 

WinH = 0; 

return(WinH); 

} 

} 

if(Legal == 3 || Legal == 10 || Legal == 17 || Legal == 24 || Legal == 31 || Legal == 38) //Checks The Middle Column 

{ 

if(Board[Legal] == Board[Legal - 3] && Board[Legal] == Board[Legal - 2] && Board[Legal] == Board[Legal - 1]) 

{ 

WinH = 1; 

return(WinH); 

} 

else if(Board[Legal] == Board[Legal + 1] && Board[Legal] == Board[Legal - 2] && Board[Legal] == Board[Legal - 1]) 

{ 

WinH = 1; 

return(WinH); 

} 

else if(Board[Legal] == Board[Legal + 1] && Board[Legal] == Board[Legal + 2] && Board[Legal] == Board[Legal - 1]) 

{ 

WinH = 1; 

return(WinH); 

} 

else if(Board[Legal] == Board[Legal + 1] && Board[Legal] == Board[Legal + 2] && Board[Legal] == Board[Legal + 3]) 

{ 

WinH = 1; 

return(WinH); 

} 

else 

{ 

WinH = 0; 

return(WinH); 

} 

} 

 

WinH = 0; //To Get Rid Of Warning Message, Will Never Actually Be Hit 

 

return(WinH); 

} 

 

 

int GameWon(char Board[], int Legal, int Place, int WinH, int WinV, int WinDT, int WinDB, int Win, int WinD) //Function That Passes Data To The Win Checker Functions And Recieves Data Back To Decide If Someone Won 

{ 

WinH = HorizontalChecker(Board, Legal, WinH); 

WinV = VerticalChecker(Board, Legal, WinV); 

WinDT = TopDiagonalChecker(Board, Legal, WinDT); 

WinDB = BottomDiagonalChecker(Board, Legal, WinDB); 

WinD = DiagonalChecker(Board, Legal, Place, WinD); 

 

Win = WinH + WinV + WinDT + WinDB + WinD; //HorizontalChecker, DiagonalChecker and VerticalChecker Both Return Values of 0 or 1, These Values Then Get Added Up And Stored In Win 

 

return(Win); 

} 

 

 

int TopDiagonalChecker(char Board[], int Legal, int WinDT) //Function To Check Diagonal Wins, Works By Checking The Head Of The Diagonal Line Which Is Only Possible In Certain Areas 

{ 

if (Legal == 0 || Legal == 1 || Legal == 2 || Legal == 7 || Legal == 8 || Legal == 9 || Legal == 14 || Legal == 15 || Legal == 16) //Checks Top Left 

{ 

if(Board[Legal] == Board[Legal + 8] && Board[Legal] == Board[Legal + 16] && Board[Legal] == Board[Legal + 24]) 

{ 

WinDT = 1; 

return(WinDT); 

} 

else 

{ 

WinDT = 0; 

return(WinDT); 

} 

} 

if (Legal == 6 || Legal == 5 || Legal == 4 || Legal == 13 || Legal == 12 || Legal == 11 || Legal == 20 || Legal == 19 || Legal == 18) //Checks Top Right 

{ 

if(Board[Legal] == Board[Legal + 6] && Board[Legal] == Board[Legal + 12] && Board[Legal] == Board[Legal + 18]) 

{ 

WinDT = 1; 

return(WinDT); 

} 

else 

{ 

WinDT = 0; 

return(WinDT); 

} 

} 

if (Legal == 3 || Legal == 10 || Legal == 17) //Checks Middle 

{ 

if(Board[Legal] == Board[Legal + 6] && Board[Legal] == Board[Legal + 12] && Board[Legal] == Board[Legal + 18]) 

{ 

WinDT = 1; 

return(WinDT); 

} 

else if (Board[Legal] == Board[Legal + 8] && Board[Legal] == Board[Legal + 16] && Board[Legal] == Board[Legal + 24]) 

{ 

WinDT = 1; 

return(WinDT); 

} 

else 

{ 

WinDT = 0; 

return(WinDT); 

} 

} 

 

WinDT = 0; //To Get Rid Of Warning Message, Will Never Actually Be Hit 

 

return(WinDT); 

} 

 

int Menu(int Input) //Creates Menu When Game Is First Run  

{ 

Input = 0; 

 

while (Input == 0) 

{ 

printf("Welcome To Connect 4!"); 

printf("\nPlease Select An Option From The List Below:"); 

printf("\nPress 1 To: Start A New Game!"); 

printf("\nPress 2 To: Load A Saved Game!"); 

printf("\nPress 3 To: Print Rules!"); 

printf("\nPress 4 To: Exit Game!"); 

printf("\n\nPlease Enter Input: "); 

 

scanf("\n%d", &Input); 

 

 

printf("\nYou Entered The Number: %d. \n", Input); 

 

while (Input < 1 || Input > 4) 

{ 

printf("\nError, Invalid Entry."); 

printf("\nPlease Enter A Valid Entry.\n"); 

scanf("%d", &Input); 

} 

 

if(Input == 3) 

{ 

printf("To Win Connect 4, All You Have To Do Is Connect Four Of Your Colored Chips In A Row.\n"); 

printf("This Can Be Done Horizontally, Vertically Or Diagonally. Each Player Will Drop \n"); 

printf("In One Chip At A Time. This Will Give You A Chance To Build Your Row, Or Stop Your Opponent From \n"); 

printf("Lining Up Four In A Row. The Game Is Over When You Or Your Friend Reaches Four In A Row, Or When All Forty \n");  

printf("Two Slots Are Filled, Causing A Stalemate. If You And Your Friend Decide To Play Again, The Loser Typically Goes First.\n"); 

Input = 0; 

} 

else if(Input == 4) 

{ 

Input = 1; 

} 

else if (Input == 1) 

{ 

Input = 27; 

} 

else if (Input == 2) 

{ 

Input = 20; 

} 

} 

 

return(Input); 

} 

 

int ReadGame(char Board[], int Counter, int Command, int H) 

{ 

FILE *iFile; 

 

iFile = fopen("Connect4Save.txt", "r"); //Opens File 

 

if(iFile != NULL) //If File Exists 

{ 

for (H = 0; H <= 41; H++) //Runs Through Loop And Gives Back Array Data 

{ 

fscanf(iFile, "%c", &Board[H]); //Prints The Data Of The Board Back To The Main 

} 

 

fscanf(iFile, "%d", &Counter); //Prints The Counter To The File So It Knows Who's Turn It Is 

 

fclose(iFile); //Closes The File 

 

Command = 100; //Sets Command To 100 And Pops It Out Of While Loop 

} 

else 

{ 

printf("Error, No File To Load!"); 

fclose(iFile); 

} 

 

return(Command); 

} 

 

int WriteGame(int G, char Board[], int Counter) 

{ 

FILE *iFile; 

 

iFile = fopen("Connect4Save.txt", "w"); //Opens A File To Save The Board To 

 

for (G = 0; G <= 41; G++) 

{ 

fprintf(iFile, "%c", Board[G]); //Prints The Data Of The Board To The File 

} 

 

fprintf(iFile, "%d", Counter); //Prints The Counter To The File So It Knows Who's Turn It Is 

 

fclose(iFile); 

 

return(0); 

} 

 

int BottomDiagonalChecker(char Board[], int Legal, int WinDB) //Function To Check Diagonal Wins, Works By Checking The Head Of The Diagonal Line Which Is Only Possible In Certain Areas 

{ 

if (Legal == 35 || Legal == 36 || Legal == 37 || Legal == 28 || Legal == 29 || Legal == 30 || Legal == 21 || Legal == 22 || Legal == 23) //Checks Top Left 

{ 

if(Board[Legal] == Board[Legal - 6] && Board[Legal] == Board[Legal - 12] && Board[Legal] == Board[Legal - 18]) 

{ 

WinDB = 1; 

return(WinDB); 

} 

else 

{ 

WinDB = 0; 

return(WinDB); 

} 

} 

if (Legal == 41 || Legal == 40 || Legal == 39 || Legal == 34 || Legal == 33 || Legal == 32 || Legal == 27 || Legal == 26 || Legal == 25) //Checks Top Right 

{ 

if(Board[Legal] == Board[Legal - 8] && Board[Legal] == Board[Legal - 16] && Board[Legal] == Board[Legal - 24]) 

{ 

printf("Hello"); 

WinDB = 1; 

return(WinDB); 

} 

else 

{ 

WinDB = 0; 

return(WinDB); 

} 

} 

if (Legal == 24 || Legal == 31 || Legal == 38) //Checks Middle 

{ 

if((Board[Legal] == Board[Legal - 6] && Board[Legal] == Board[Legal - 12] && Board[Legal] == Board[Legal - 18])) 

{ 

WinDB = 1; 

return(WinDB); 

} 

else if (Board[Legal] == Board[Legal - 8] && Board[Legal] == Board[Legal - 16] && Board[Legal] == Board[Legal - 24]) 

{ 

WinDB = 1; 

return(WinDB); 

} 

else 

{ 

WinDB = 0; 

return(WinDB); 

} 

}  

 

WinDB = 0; //To Get Rid Of Warning Message, Will Never Actually Be Hit 

 

return(WinDB); 

} 

 

int DiagonalChecker(char Board[], int Legal, int Place, int WinD) 

{ 

if (Place <= 3 && Legal > 20) 

{ 

if((Board[Legal] == Board[Legal - 6] && Board[Legal] == Board[Legal - 12] && Board[Legal] == Board[Legal - 18])) 

{ 

WinD = 1; 

return(WinD); 

} 

} 

if(Place <= 4 && Place >= 1 && Legal < 34 && Legal > 13) 

{ 

if((Board[Legal] == Board[Legal - 6] && Board[Legal] == Board[Legal - 12] && Board[Legal] == Board[Legal + 6])) 

{ 

WinD = 1; 

return(WinD); 

 

} 

} 

if (Place <= 5 && Place >= 2 && Legal < 27 && Legal > 6) 

{ 

if((Board[Legal] == Board[Legal - 6] && Board[Legal] == Board[Legal + 12] && Board[Legal] == Board[Legal + 6])) 

{ 

WinD = 1; 

return(WinD); 

 

} 

} 

if (Place <= 6 && Place >= 3 && Legal < 21 && Legal > 0) 

{ 

if((Board[Legal] == Board[Legal + 6] && Board[Legal] == Board[Legal + 12] && Board[Legal] == Board[Legal + 18])) 

{ 

WinD = 1; 

return(WinD); 

 

} 

} 

if (Place >= 3 && Place <= 6 && Legal > 20 && Legal < 42) 

{ 

if((Board[Legal] == Board[Legal - 8] && Board[Legal] == Board[Legal - 16] && Board[Legal] == Board[Legal - 24])) 

{ 

WinD = 1; 

return(WinD); 

 

} 

} 

if (Place <= 5 && Place >= 2 && Legal < 34 && Legal > 13) 

{ 

if((Board[Legal] == Board[Legal + 8] && Board[Legal] == Board[Legal - 16] && Board[Legal] == Board[Legal - 8])) 

{ 

WinD = 1; 

return(WinD); 

 

} 

} 

if (Place <= 4 && Place >= 1 && Legal < 28 && Legal > 6) 

{ 

if((Board[Legal] == Board[Legal - 8] && Board[Legal] == Board[Legal + 8] && Board[Legal] == Board[Legal + 16])) 

{ 

WinD = 1; 

return(WinD); 

 

} 

} 

if (Place <= 3 && Place >= 0 && Legal < 20 && Legal > -1) 

{ 

if((Board[Legal] == Board[Legal + 8] && Board[Legal] == Board[Legal + 16] && Board[Legal] == Board[Legal + 24])) 

{ 

WinD = 1; 

return(WinD); 

 

} 

} 

else 

{ 

WinD = 0; 

return(WinD); 

} 

 

WinD =0; 

return(WinD); 

} 