#include "gnudiff_diff.h"
#include "common.h"

class Selection
{
public:
  Selection(){}
private:
  const LineRef invalidRef = -1;
  LineRef firstLine = invalidRef;
  LineRef lastLine = invalidRef;

  int firstPos = -1;
  int lastPos = -1;
  
  LineRef oldFirstLine = invalidRef;
  LineRef oldLastLine = invalidRef;
public:
//private:
  bool bSelectionContainsData = false;
public:
  inline LineRef getFirstLine() { return firstLine; };
  inline LineRef getLastLine() { return lastLine; };

  inline int getFirstPos() { return firstPos; };
  inline int getLastPos() { return lastPos; };

  inline bool isValidFirstLine() { return firstLine != invalidRef; }
  inline void clearOldSelection() { oldLastLine = invalidRef, oldFirstLine = invalidRef; };
  
  inline LineRef getOldLastLine() { return oldLastLine; };
  inline LineRef getOldFirstLine() { return oldFirstLine; };
  inline bool selectionContainsData(void) { return bSelectionContainsData; };
  bool isEmpty() { return firstLine == invalidRef || (firstLine == lastLine && firstPos == lastPos) || bSelectionContainsData == false; }
  void reset()
  {
      oldLastLine = lastLine;
      oldFirstLine = firstLine;
      firstLine = invalidRef;
      lastLine = invalidRef;
      bSelectionContainsData = false;
   }
   void start( LineRef l, int p ) { firstLine = l; firstPos = p; }
   void end( LineRef l, int p )  {
      if ( oldLastLine == invalidRef )
         oldLastLine = lastLine;
      lastLine  = l;
      lastPos  = p;
      //bSelectionContainsData = (firstLine == lastLine && firstPos == lastPos);
   }
   bool within( LineRef l, LineRef p );

   bool lineWithin( LineRef l );
   int firstPosInLine(LineRef l);
   int lastPosInLine(LineRef l);
   LineRef beginLine(){ 
      if (firstLine<0 && lastLine<0) return invalidRef;
      return max2((LineRef)0,min2(firstLine,lastLine)); 
   }
   LineRef endLine(){ 
      if (firstLine<0 && lastLine<0) return invalidRef;
      return max2(firstLine,lastLine); 
   }
   int beginPos() { return firstLine==lastLine ? min2(firstPos,lastPos) :
                           firstLine<lastLine ? (firstLine<0?0:firstPos) : (lastLine<0?0:lastPos);  }
   int endPos()   { return firstLine==lastLine ? max2(firstPos,lastPos) :
                           firstLine<lastLine ? lastPos : firstPos;      }
};