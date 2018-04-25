// Bryan Xie
// byx150030@utdallas.edu
// CS 3377.502

#include <iostream>
#include "cdk.h"
#include "binaryClasses.h"
#include <fstream>
#include <iomanip>
#include <string>

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 17
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
    drawCDKMatrix(myMatrix, true);

  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecord1 = new BinaryFileRecord();
  BinaryFileRecord *myRecord2 = new BinaryFileRecord();
  BinaryFileRecord *myRecord3 = new BinaryFileRecord();
  BinaryFileRecord *myRecord4 = new BinaryFileRecord();
  
  ifstream binInfile("cs3377.bin", ios::in | ios::binary);

  char buffer1[30];
  char buffer2[10];
  char buffer3[10];

  char buffer4[10];
  char buffer5[10];
  char buffer6[10];
  char buffer7[10];

  char temp1[20] = "Magic: ";
  char temp2[20] = "Version: ";
  char temp3[20] = "NumRecords: ";
  char temp4[20] = "strlen: ";
  char temp5[20] = "strlen: ";
  char temp6[20] = "strlen: ";
  char temp7[20] = "strlen: ";

  int size = 0;

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  sprintf(buffer1,"0x%.8X", myHeader -> magicNumber);
  sprintf(buffer2,"%d", myHeader -> versionNumber);
  sprintf(buffer3,"%d", myHeader -> numRecords);


  while (!binInfile.eof() && size < 4)
    {  
      if (size == 0)
	{
      binInfile.read((char *) myRecord1, sizeof(BinaryFileRecord));
      sprintf(buffer4,"%d", myRecord1 -> strLength);
	}
      else if (size == 1)
	{
  binInfile.read((char *) myRecord2, sizeof(BinaryFileRecord));
  sprintf(buffer5,"%d", myRecord2 -> strLength);
	}
      else if (size == 2)
	{
  binInfile.read((char *) myRecord3, sizeof(BinaryFileRecord));
  sprintf(buffer6,"%d", myRecord3 -> strLength);
	}
      else if (size == 3)
	{
  binInfile.read((char *) myRecord4, sizeof(BinaryFileRecord));
  sprintf(buffer7,"%d", myRecord4 -> strLength);
	}
      size++;
    }
  binInfile.close();

  /*
   * Display a message
   */

  setCDKMatrixCell(myMatrix, 1, 1, strcat(temp1,buffer1));
  setCDKMatrixCell(myMatrix, 1, 2, strcat(temp2,buffer2));
  setCDKMatrixCell(myMatrix, 1, 3, strcat(temp3,buffer3));

  setCDKMatrixCell(myMatrix, 2, 1, strcat(temp4,buffer4)); 
  setCDKMatrixCell(myMatrix, 2, 2, myRecord1 -> stringBuffer);
  setCDKMatrixCell(myMatrix, 3, 1, strcat(temp5,buffer5));
  setCDKMatrixCell(myMatrix, 3, 2, myRecord2 -> stringBuffer);
  setCDKMatrixCell(myMatrix, 4, 1, strcat(temp6,buffer6));
  setCDKMatrixCell(myMatrix, 4, 2, myRecord3 -> stringBuffer);
  setCDKMatrixCell(myMatrix, 5, 1, strcat(temp7,buffer7));
  setCDKMatrixCell(myMatrix, 5, 2, myRecord4 -> stringBuffer);

  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
  return 0;
}
