// Scintilla source code edit control
/** @file LexAIPI.cxx
 ** Lexer for AIPI, C++, C, Java, and JavaScript.
 **/
// Copyright 1998-2005 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.
    
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>



#include "Platform.h"

#include "PropSet.h"
#include "Accessor.h"
#include "StyleContext.h"
#include "KeyWords.h"
#include "Scintilla.h"
#include "SciLexer.h"

#define SET_LOWER "abcdefghijklmnopqrstuvwxyz"
#define SET_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define SET_DIGITS "0123456789"

class SetOfCharacters {
	int size;
	bool valueAfter;
	bool *bset;
public:
	SetOfCharacters(const char *setOfCharacters, int size_=0x80, bool valueAfter_=false) {
		size = size_;
		valueAfter = valueAfter_;
		bset = new bool[size];
		for (int i=0; i < size; i++) {
			bset[i] = false;
		}
		for (const char *cp=setOfCharacters; *cp; cp++) {
			int val = static_cast<unsigned char>(*cp);
			PLATFORM_ASSERT(val >= 0);
			PLATFORM_ASSERT(val < size);
			bset[val] = true;
		}
	}
	~SetOfCharacters() {
		delete []bset;
		bset = 0;
		size = 0;
	}
	void Add(int val) {
		PLATFORM_ASSERT(val >= 0);
		PLATFORM_ASSERT(val < size);
		bset[val] = true;
	}
	bool Contains(int val) {
		PLATFORM_ASSERT(val >= 0);
		return (val < size) ? bset[val] : valueAfter;
	}
};

static bool IsSpaceEquiv(int state) {
	return (state <= SCE_C_COMMENTDOC) ||
		// including SCE_C_DEFAULT, SCE_C_COMMENT, SCE_C_COMMENTLINE
		(state == SCE_C_COMMENTLINEDOC) || (state == SCE_C_COMMENTDOCKEYWORD) ||
		(state == SCE_C_COMMENTDOCKEYWORDERROR);
}

static void ColouriseAIPIDoc(unsigned int startPos, int length, int initStyle, WordList *keywordlists[],
                            Accessor &styler, bool caseSensitive) {

	WordList &keywords = *keywordlists[0];
	WordList &keywords2 = *keywordlists[1];
	WordList &keywords3 = *keywordlists[2];
	WordList &keywords4 = *keywordlists[3];

	bool stylingWithinPreprocessor = styler.GetPropertyInt("styling.within.preprocessor") != 0;

	SetOfCharacters setOKBeforeRE("(=,");

	SetOfCharacters setDoxygen("$@\\&<>#{}[]" SET_LOWER);

	SetOfCharacters setWordStart("_" SET_LOWER SET_UPPER, 0x80, true);
	SetOfCharacters setWord("._" SET_LOWER SET_UPPER SET_DIGITS, 0x80, true);
/*	if (styler.GetPropertyInt("lexer.cpp.allow.dollars", 1) != 0) {
		setWordStart.Add('$');
		setWord.Add('$');
	}
*/
	int chPrevNonWhite = ' ';
	int visibleChars = 0;
	bool lastWordWasUUID = false;
	int styleBeforeDCKeyword = SCE_AIPI_DEFAULT;
	bool continuationLine = false;

	if (initStyle == SCE_AIPI_PREPROCESSOR) {
		// Set continuationLine if last character of previous line is '\'
		int lineCurrent = styler.GetLine(startPos);
		if (lineCurrent > 0) {
			int chBack = styler.SafeGetCharAt(startPos-1, 0);
			int chBack2 = styler.SafeGetCharAt(startPos-2, 0);
			int lineEndChar = '!';
			if (chBack2 == '\r' && chBack == '\n') {
				lineEndChar = styler.SafeGetCharAt(startPos-3, 0);
			} else if (chBack == '\n' || chBack == '\r') {
				lineEndChar = chBack2;
			}
			continuationLine = lineEndChar == '\\';
		}
	}

	// look back to set chPrevNonWhite properly for better regex colouring
	if (startPos > 0) {
		int back = startPos;
		while (--back && IsSpaceEquiv(styler.StyleAt(back)))
			;
		if (styler.StyleAt(back) == SCE_C_OPERATOR) {
			chPrevNonWhite = styler.SafeGetCharAt(back);
		}
	}

	StyleContext sc(startPos, length, initStyle, styler);

	for (; sc.More(); sc.Forward()) {

		if (sc.atLineStart) {
			if (sc.state == SCE_AIPI_STRING) {
				// Prevent SCE_C_STRINGEOL from leaking back to previous line which
				// ends with a line continuation by locking in the state upto this position.
				sc.SetState(SCE_AIPI_STRING);
			}
		
/* Nuevo código */
			if (sc.state == SCE_AIPI_VAR) {
				// Prevent SCE_C_STRINGEOL from leaking back to previous line which
				// ends with a line continuation by locking in the state upto this position.
				sc.SetState(SCE_AIPI_VAR);
			}
			if (sc.state == SCE_AIPI_PROP) {
				// Prevent SCE_C_STRINGEOL from leaking back to previous line which
				// ends with a line continuation by locking in the state upto this position.
				sc.SetState(SCE_AIPI_PROP);
			}

/* Fin de código */
			// Reset states to begining of colourise so no surprises
			// if different sets of lines lexed.
			visibleChars = 0;
			lastWordWasUUID = false;
		}

		// Handle line continuation generically.
		if (sc.ch == '\\') {
			if (sc.chNext == '\n' || sc.chNext == '\r') {
				sc.Forward();
				if (sc.ch == '\r' && sc.chNext == '\n') {
					sc.Forward();
				}
				continuationLine = true;
				continue;
			}
		}

		// Determine if the current state should terminate.
		switch (sc.state) {
			case SCE_AIPI_OPERATOR:
				sc.SetState(SCE_C_DEFAULT);
				break;
			case SCE_AIPI_NUMBER:
				// We accept almost anything because of hex. and number suffixes
				if (!setWord.Contains(sc.ch)) {
					sc.SetState(SCE_AIPI_DEFAULT);
				}
				break;
			case SCE_AIPI_IDENTIFIER:
				if (!setWord.Contains(sc.ch) || (sc.ch == '.')) {
					char s[1000];
					if (caseSensitive) {
						sc.GetCurrent(s, sizeof(s));
					} else {
						sc.GetCurrentLowered(s, sizeof(s));
					}
					if (keywords.InList(s)) {
						lastWordWasUUID = strcmp(s, "uuid") == 0;
						sc.ChangeState(SCE_AIPI_WORD);
					} else if (keywords2.InList(s)) {
						sc.ChangeState(SCE_AIPI_WORD2);
					} else if (keywords4.InList(s)) {
						sc.ChangeState(SCE_AIPI_GLOBALCLASS);
					}
					sc.SetState(SCE_AIPI_DEFAULT);
				}
				break;
			case SCE_AIPI_PREPROCESSOR:
				if (sc.atLineStart && !continuationLine) {
					sc.SetState(SCE_AIPI_DEFAULT);
				} else if (stylingWithinPreprocessor) {
					if (IsASpace(sc.ch)) {
						sc.SetState(SCE_AIPI_DEFAULT);
					}
				} else {
					if (sc.Match('/', '*') || sc.Match('/', '/')) {
						sc.SetState(SCE_AIPI_DEFAULT);
					}
				}
				break;
			case SCE_AIPI_COMMENT:
				if (sc.Match('*', '/')) {
					sc.Forward();
					sc.ForwardSetState(SCE_AIPI_DEFAULT);
				}
				break;
			case SCE_AIPI_COMMENTDOC:
				if (sc.Match('*', '/')) {
					sc.Forward();
					sc.ForwardSetState(SCE_AIPI_DEFAULT);
				} else if (sc.ch == '@' || sc.ch == '\\') { // JavaDoc and Doxygen support
					// Verify that we have the conditions to mark a comment-doc-keyword
					if ((IsASpace(sc.chPrev) || sc.chPrev == '*') && (!IsASpace(sc.chNext))) {
						styleBeforeDCKeyword = SCE_AIPI_COMMENTDOC;
						sc.SetState(SCE_AIPI_COMMENTDOCKEYWORD);
					}
				}
				break;
			case SCE_AIPI_COMMENTLINE:
				if (sc.atLineStart) {
					sc.SetState(SCE_AIPI_DEFAULT);
				}
				break;
			case SCE_AIPI_COMMENTLINEDOC:
				if (sc.atLineStart) {
					sc.SetState(SCE_AIPI_DEFAULT);
				} else if (sc.ch == '@' || sc.ch == '\\') { // JavaDoc and Doxygen support
					// Verify that we have the conditions to mark a comment-doc-keyword
					if ((IsASpace(sc.chPrev) || sc.chPrev == '/' || sc.chPrev == '!') && (!IsASpace(sc.chNext))) {
						styleBeforeDCKeyword = SCE_AIPI_COMMENTLINEDOC;
						sc.SetState(SCE_AIPI_COMMENTDOCKEYWORD);
					}
				}
				break;
			case SCE_AIPI_COMMENTDOCKEYWORD:
				if ((styleBeforeDCKeyword == SCE_AIPI_COMMENTDOC) && sc.Match('*', '/')) {
					sc.ChangeState(SCE_AIPI_COMMENTDOCKEYWORDERROR);
					sc.Forward();
					sc.ForwardSetState(SCE_AIPI_DEFAULT);
				} else if (!setDoxygen.Contains(sc.ch)) {
					char s[100];
					if (caseSensitive) {
						sc.GetCurrent(s, sizeof(s));
					} else {
						sc.GetCurrentLowered(s, sizeof(s));
					}
					if (!IsASpace(sc.ch) || !keywords3.InList(s + 1)) {
						sc.ChangeState(SCE_AIPI_COMMENTDOCKEYWORDERROR);
					}
					sc.SetState(styleBeforeDCKeyword);
				}
				break;
			
			case SCE_AIPI_STRING:
				if (sc.atLineEnd) {
					sc.ChangeState(SCE_AIPI_STRINGEOL);
				} else if (sc.ch == '\\') {
					if (sc.chNext == '\"' || sc.chNext == '\'' || sc.chNext == '\\') {
						sc.Forward();
					}
				} else if (sc.ch == '\"') {
					sc.ForwardSetState(SCE_AIPI_DEFAULT);
				}
				break;
			case SCE_AIPI_CHARACTER:
				if (sc.atLineEnd) {
					sc.ChangeState(SCE_AIPI_STRINGEOL);
				} else if (sc.ch == '\\') {
					if (sc.chNext == '\"' || sc.chNext == '\'' || sc.chNext == '\\') {
						sc.Forward();
					}
				} else if (sc.ch == '\'') {
					sc.ForwardSetState(SCE_AIPI_DEFAULT);
				}
				break;
			
/* Nuevo código */ 

			case SCE_AIPI_VAR:
				if (sc.atLineEnd) {
					sc.ChangeState(SCE_AIPI_STRINGEOL);
				} else if (sc.ch == '\\') {
					if (sc.chNext == '\"' || sc.chNext == '\'' || sc.chNext == '\\') {
					//if (sc.chNext == '$' ) {
						sc.Forward();
					}
				} else if (sc.ch == '$') {
					sc.ForwardSetState(SCE_AIPI_DEFAULT);
				}
				break;
			case SCE_AIPI_PROP:
				if (sc.atLineEnd) {
					sc.ChangeState(SCE_AIPI_STRINGEOL);
				} else if (sc.ch == '\\') {
					//if (sc.chNext == '|' ) {
					if (sc.chNext == '\"' || sc.chNext == '\'' || sc.chNext == '\\') {
						sc.Forward();
					}
				} else if (sc.ch == ']') {
					sc.ForwardSetState(SCE_AIPI_DEFAULT);
				}
				break;

/* fin de código */

			case SCE_AIPI_REGEX:
				if (sc.atLineStart) {
					sc.SetState(SCE_AIPI_DEFAULT);
				} else if (sc.ch == '/') {
					sc.Forward();
					while ((sc.ch < 0x80) && islower(sc.ch))
						sc.Forward();    // gobble regex flags
					sc.SetState(SCE_AIPI_DEFAULT);
				} else if (sc.ch == '\\') {
					// Gobble up the quoted character
					if (sc.chNext == '\\' || sc.chNext == '/') {
						sc.Forward();
					}
				}
				break;
			case SCE_AIPI_STRINGEOL:
				if (sc.atLineStart) {
					sc.SetState(SCE_AIPI_DEFAULT);
				}
				break;
			case SCE_AIPI_VERBATIM:
				if (sc.ch == '\"') {
					if (sc.chNext == '\"') {
						sc.Forward();
					} else {
						sc.ForwardSetState(SCE_AIPI_DEFAULT);
					}
				}
				break;
			case SCE_AIPI_UUID:
				if (sc.ch == '\r' || sc.ch == '\n' || sc.ch == ')') {
					sc.SetState(SCE_AIPI_DEFAULT);
				}
		}

		// Determine if a new state should be entered.
		if (sc.state == SCE_AIPI_DEFAULT) {
			if (sc.Match('@', '\"')) {
				sc.SetState(SCE_AIPI_VERBATIM);
				sc.Forward();
			} else if (IsADigit(sc.ch) || (sc.ch == '.' && IsADigit(sc.chNext))) {
				if (lastWordWasUUID) {
					sc.SetState(SCE_AIPI_UUID);
					lastWordWasUUID = false;
				} else {
					sc.SetState(SCE_AIPI_NUMBER);
				}
			} else if (setWordStart.Contains(sc.ch) || (sc.ch == '@')) {
				if (lastWordWasUUID) {
					sc.SetState(SCE_AIPI_UUID);
					lastWordWasUUID = false;
				} else {
					sc.SetState(SCE_AIPI_IDENTIFIER);
				}
			} else if (sc.Match('/', '*')) {
				if (sc.Match("/**") || sc.Match("/*!")) {	// Support of Qt/Doxygen doc. style
					sc.SetState(SCE_AIPI_COMMENTDOC);
				} else {
					sc.SetState(SCE_AIPI_COMMENT);
				}
				sc.Forward();	// Eat the * so it isn't used for the end of the comment
			} else if (sc.Match('/', '/')) {
				if ((sc.Match("///") && !sc.Match("////")) || sc.Match("//!"))
					// Support of Qt/Doxygen doc. style
					sc.SetState(SCE_AIPI_COMMENTLINEDOC);
				else
					sc.SetState(SCE_AIPI_COMMENTLINE);
			} else if (sc.ch == '/' && setOKBeforeRE.Contains(chPrevNonWhite)) {
				sc.SetState(SCE_AIPI_REGEX);	// JavaScript's RegEx
			} else if (sc.ch == '\"') {
				sc.SetState(SCE_AIPI_STRING); 
			} else if (sc.ch == '\'') {
				sc.SetState(SCE_AIPI_CHARACTER);

/* Nuevo código */

			} else if (sc.ch == '$') {
				sc.SetState(SCE_AIPI_VAR);
			} else if (sc.ch == '[') {
				sc.SetState(SCE_AIPI_PROP);

/* Fin de código */

			} else if (sc.ch == '#' && visibleChars == 0) {
				// Preprocessor commands are alone on their line
				sc.SetState(SCE_AIPI_PREPROCESSOR);
				// Skip whitespace between # and preprocessor word
				do {
					sc.Forward();
				} while ((sc.ch == ' ' || sc.ch == '\t') && sc.More());
				if (sc.atLineEnd) {
					sc.SetState(SCE_AIPI_DEFAULT);
				}
			} else if (isoperator(static_cast<char>(sc.ch))) {
				sc.SetState(SCE_AIPI_OPERATOR);
			}
		}

		if (!IsASpace(sc.ch) && !IsSpaceEquiv(sc.state)) {
			chPrevNonWhite = sc.ch;
			visibleChars++;
		}
		continuationLine = false;
	}
	sc.Complete();
}

static bool IsStreamCommentStyle(int style) {
	return style == SCE_AIPI_COMMENT ||
		style == SCE_AIPI_COMMENTDOC ||
		style == SCE_AIPI_COMMENTDOCKEYWORD ||
		style == SCE_AIPI_COMMENTDOCKEYWORDERROR;
}

// Store both the current line's fold level and the next lines in the
// level store to make it easy to pick up with each increment
// and to make it possible to fiddle the current level for "} else {".
static void FoldNoBoxCppDoc(unsigned int startPos, int length, int initStyle,
                            Accessor &styler) {
	bool foldComment = styler.GetPropertyInt("fold.comment") != 0;
	bool foldPreprocessor = styler.GetPropertyInt("fold.preprocessor") != 0;
	bool foldCompact = styler.GetPropertyInt("fold.compact", 1) != 0;
	bool foldAtElse = styler.GetPropertyInt("fold.at.else", 0) != 0;
	unsigned int endPos = startPos + length;
	int visibleChars = 0;
	int lineCurrent = styler.GetLine(startPos);
	int levelCurrent = SC_FOLDLEVELBASE;
	if (lineCurrent > 0)
		levelCurrent = styler.LevelAt(lineCurrent-1) >> 16;
	int levelMinCurrent = levelCurrent;
	int levelNext = levelCurrent;
	char chNext = styler[startPos];
	int styleNext = styler.StyleAt(startPos);
	int style = initStyle;
	for (unsigned int i = startPos; i < endPos; i++) {
		char ch = chNext;
		chNext = styler.SafeGetCharAt(i + 1);
		int stylePrev = style;
		style = styleNext;
		styleNext = styler.StyleAt(i + 1);
		bool atEOL = (ch == '\r' && chNext != '\n') || (ch == '\n');
		if (foldComment && IsStreamCommentStyle(style)) {
			if (!IsStreamCommentStyle(stylePrev)) {
				levelNext++;
			} else if (!IsStreamCommentStyle(styleNext) && !atEOL) {
				// Comments don't end at end of line and the next character may be unstyled.
				levelNext--;
			}
		}
		if (foldComment && (style == SCE_AIPI_COMMENTLINE)) {
			if ((ch == '/') && (chNext == '/')) {
				char chNext2 = styler.SafeGetCharAt(i + 2);
				if (chNext2 == '{') {
					levelNext++;
				} else if (chNext2 == '}') {
					levelNext--;
				}
			}
		}
		if (foldPreprocessor && (style == SCE_AIPI_PREPROCESSOR)) {
			if (ch == '#') {
				unsigned int j = i + 1;
				while ((j < endPos) && IsASpaceOrTab(styler.SafeGetCharAt(j))) {
					j++;
				}
				if (styler.Match(j, "region") || styler.Match(j, "if")) {
					levelNext++;
				} else if (styler.Match(j, "end")) {
					levelNext--;
				}
			}
		}
		if (style == SCE_AIPI_OPERATOR) {
			if (ch == '{') {
				// Measure the minimum before a '{' to allow
				// folding on "} else {"
				if (levelMinCurrent > levelNext) {
					levelMinCurrent = levelNext;
				}
				levelNext++;
			} else if (ch == '}') {
				levelNext--;
			}
		}
		if (atEOL) {
			int levelUse = levelCurrent;
			if (foldAtElse) {
				levelUse = levelMinCurrent;
			}
			int lev = levelUse | levelNext << 16;
			if (visibleChars == 0 && foldCompact)
				lev |= SC_FOLDLEVELWHITEFLAG;
			if (levelUse < levelNext)
				lev |= SC_FOLDLEVELHEADERFLAG;
			if (lev != styler.LevelAt(lineCurrent)) {
				styler.SetLevel(lineCurrent, lev);
			}
			lineCurrent++;
			levelCurrent = levelNext;
			levelMinCurrent = levelCurrent;
			visibleChars = 0;
		}
		if (!IsASpace(ch))
			visibleChars++;
	}
}

static void FoldAIPIDoc(unsigned int startPos, int length, int initStyle, WordList *[],
                       Accessor &styler) {
	FoldNoBoxCppDoc(startPos, length, initStyle, styler);
}

static const char * const AIPIWordLists[] = {
            "Primary keywords and identifiers",
            "Secondary keywords and identifiers",
            "Documentation comment keywords",
            "Unused",
            "Global classes and typedefs",
            0,
        };

static void ColouriseAIPIDocSensitive(unsigned int startPos, int length, int initStyle, WordList *keywordlists[],
                                     Accessor &styler) {
	ColouriseAIPIDoc(startPos, length, initStyle, keywordlists, styler, true);
}

static void ColouriseAIPIDocInsensitive(unsigned int startPos, int length, int initStyle, WordList *keywordlists[],
                                       Accessor &styler) {
	ColouriseAIPIDoc(startPos, length, initStyle, keywordlists, styler, false);
}

/* Modificación del código */

LexerModule lmAIPI(SCLEX_AIPI, ColouriseAIPIDocSensitive, "knw", FoldAIPIDoc, AIPIWordLists);
LexerModule lmAIPINoCase(SCLEX_AIPINOCASE, ColouriseAIPIDocInsensitive, "knwnocase", FoldAIPIDoc, AIPIWordLists);
