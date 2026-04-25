// Generated from /home/jochen/workdir/YAIP/src/lib/antlr/IniParser.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class IniParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		LBRACK=1, RBRACK=2, EQUAL=3, SEMI=4, NL=5, TEXT=6;
	public static final int
		RULE_iniFile = 0, RULE_statement = 1, RULE_sectionStatement = 2, RULE_pairStatement = 3, 
		RULE_commentStatement = 4, RULE_comment = 5, RULE_text = 6;
	private static String[] makeRuleNames() {
		return new String[] {
			"iniFile", "statement", "sectionStatement", "pairStatement", "commentStatement", 
			"comment", "text"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'['", "']'", "'='"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "LBRACK", "RBRACK", "EQUAL", "SEMI", "NL", "TEXT"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "IniParser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public IniParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IniFileContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(IniParser.EOF, 0); }
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public IniFileContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_iniFile; }
	}

	public final IniFileContext iniFile() throws RecognitionException {
		IniFileContext _localctx = new IniFileContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_iniFile);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(17);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 114L) != 0)) {
				{
				{
				setState(14);
				statement();
				}
				}
				setState(19);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(20);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StatementContext extends ParserRuleContext {
		public SectionStatementContext sectionStatement() {
			return getRuleContext(SectionStatementContext.class,0);
		}
		public PairStatementContext pairStatement() {
			return getRuleContext(PairStatementContext.class,0);
		}
		public CommentStatementContext commentStatement() {
			return getRuleContext(CommentStatementContext.class,0);
		}
		public TerminalNode NL() { return getToken(IniParser.NL, 0); }
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_statement);
		try {
			setState(26);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(22);
				sectionStatement();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(23);
				pairStatement();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(24);
				commentStatement();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(25);
				match(NL);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SectionStatementContext extends ParserRuleContext {
		public TextContext name;
		public TerminalNode LBRACK() { return getToken(IniParser.LBRACK, 0); }
		public TerminalNode RBRACK() { return getToken(IniParser.RBRACK, 0); }
		public CommentContext comment() {
			return getRuleContext(CommentContext.class,0);
		}
		public TerminalNode NL() { return getToken(IniParser.NL, 0); }
		public TextContext text() {
			return getRuleContext(TextContext.class,0);
		}
		public SectionStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_sectionStatement; }
	}

	public final SectionStatementContext sectionStatement() throws RecognitionException {
		SectionStatementContext _localctx = new SectionStatementContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_sectionStatement);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(28);
			match(LBRACK);
			setState(30);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==TEXT) {
				{
				setState(29);
				((SectionStatementContext)_localctx).name = text();
				}
			}

			setState(32);
			match(RBRACK);
			setState(34);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				{
				setState(33);
				comment();
				}
				break;
			}
			setState(37);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
			case 1:
				{
				setState(36);
				match(NL);
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PairStatementContext extends ParserRuleContext {
		public TextContext key;
		public TextContext value;
		public TerminalNode EQUAL() { return getToken(IniParser.EQUAL, 0); }
		public List<TextContext> text() {
			return getRuleContexts(TextContext.class);
		}
		public TextContext text(int i) {
			return getRuleContext(TextContext.class,i);
		}
		public CommentContext comment() {
			return getRuleContext(CommentContext.class,0);
		}
		public TerminalNode NL() { return getToken(IniParser.NL, 0); }
		public PairStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pairStatement; }
	}

	public final PairStatementContext pairStatement() throws RecognitionException {
		PairStatementContext _localctx = new PairStatementContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_pairStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(39);
			((PairStatementContext)_localctx).key = text();
			setState(40);
			match(EQUAL);
			setState(42);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
			case 1:
				{
				setState(41);
				((PairStatementContext)_localctx).value = text();
				}
				break;
			}
			setState(45);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,6,_ctx) ) {
			case 1:
				{
				setState(44);
				comment();
				}
				break;
			}
			setState(48);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				{
				setState(47);
				match(NL);
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class CommentStatementContext extends ParserRuleContext {
		public TerminalNode SEMI() { return getToken(IniParser.SEMI, 0); }
		public List<TextContext> text() {
			return getRuleContexts(TextContext.class);
		}
		public TextContext text(int i) {
			return getRuleContext(TextContext.class,i);
		}
		public TerminalNode NL() { return getToken(IniParser.NL, 0); }
		public CommentStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_commentStatement; }
	}

	public final CommentStatementContext commentStatement() throws RecognitionException {
		CommentStatementContext _localctx = new CommentStatementContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_commentStatement);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(51);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==TEXT) {
				{
				setState(50);
				text();
				}
			}

			setState(53);
			match(SEMI);
			setState(55);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,9,_ctx) ) {
			case 1:
				{
				setState(54);
				text();
				}
				break;
			}
			setState(58);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,10,_ctx) ) {
			case 1:
				{
				setState(57);
				match(NL);
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class CommentContext extends ParserRuleContext {
		public TerminalNode SEMI() { return getToken(IniParser.SEMI, 0); }
		public TextContext text() {
			return getRuleContext(TextContext.class,0);
		}
		public CommentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_comment; }
	}

	public final CommentContext comment() throws RecognitionException {
		CommentContext _localctx = new CommentContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_comment);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(60);
			match(SEMI);
			setState(62);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,11,_ctx) ) {
			case 1:
				{
				setState(61);
				text();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TextContext extends ParserRuleContext {
		public List<TerminalNode> TEXT() { return getTokens(IniParser.TEXT); }
		public TerminalNode TEXT(int i) {
			return getToken(IniParser.TEXT, i);
		}
		public TextContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_text; }
	}

	public final TextContext text() throws RecognitionException {
		TextContext _localctx = new TextContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_text);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(65); 
			_errHandler.sync(this);
			_alt = 1;
			do {
				switch (_alt) {
				case 1:
					{
					{
					setState(64);
					match(TEXT);
					}
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				setState(67); 
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,12,_ctx);
			} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\u0004\u0001\u0006F\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0001\u0000\u0005\u0000\u0010"+
		"\b\u0000\n\u0000\f\u0000\u0013\t\u0000\u0001\u0000\u0001\u0000\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0003\u0001\u001b\b\u0001\u0001\u0002"+
		"\u0001\u0002\u0003\u0002\u001f\b\u0002\u0001\u0002\u0001\u0002\u0003\u0002"+
		"#\b\u0002\u0001\u0002\u0003\u0002&\b\u0002\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0003\u0003+\b\u0003\u0001\u0003\u0003\u0003.\b\u0003\u0001\u0003"+
		"\u0003\u00031\b\u0003\u0001\u0004\u0003\u00044\b\u0004\u0001\u0004\u0001"+
		"\u0004\u0003\u00048\b\u0004\u0001\u0004\u0003\u0004;\b\u0004\u0001\u0005"+
		"\u0001\u0005\u0003\u0005?\b\u0005\u0001\u0006\u0004\u0006B\b\u0006\u000b"+
		"\u0006\f\u0006C\u0001\u0006\u0000\u0000\u0007\u0000\u0002\u0004\u0006"+
		"\b\n\f\u0000\u0000M\u0000\u0011\u0001\u0000\u0000\u0000\u0002\u001a\u0001"+
		"\u0000\u0000\u0000\u0004\u001c\u0001\u0000\u0000\u0000\u0006\'\u0001\u0000"+
		"\u0000\u0000\b3\u0001\u0000\u0000\u0000\n<\u0001\u0000\u0000\u0000\fA"+
		"\u0001\u0000\u0000\u0000\u000e\u0010\u0003\u0002\u0001\u0000\u000f\u000e"+
		"\u0001\u0000\u0000\u0000\u0010\u0013\u0001\u0000\u0000\u0000\u0011\u000f"+
		"\u0001\u0000\u0000\u0000\u0011\u0012\u0001\u0000\u0000\u0000\u0012\u0014"+
		"\u0001\u0000\u0000\u0000\u0013\u0011\u0001\u0000\u0000\u0000\u0014\u0015"+
		"\u0005\u0000\u0000\u0001\u0015\u0001\u0001\u0000\u0000\u0000\u0016\u001b"+
		"\u0003\u0004\u0002\u0000\u0017\u001b\u0003\u0006\u0003\u0000\u0018\u001b"+
		"\u0003\b\u0004\u0000\u0019\u001b\u0005\u0005\u0000\u0000\u001a\u0016\u0001"+
		"\u0000\u0000\u0000\u001a\u0017\u0001\u0000\u0000\u0000\u001a\u0018\u0001"+
		"\u0000\u0000\u0000\u001a\u0019\u0001\u0000\u0000\u0000\u001b\u0003\u0001"+
		"\u0000\u0000\u0000\u001c\u001e\u0005\u0001\u0000\u0000\u001d\u001f\u0003"+
		"\f\u0006\u0000\u001e\u001d\u0001\u0000\u0000\u0000\u001e\u001f\u0001\u0000"+
		"\u0000\u0000\u001f \u0001\u0000\u0000\u0000 \"\u0005\u0002\u0000\u0000"+
		"!#\u0003\n\u0005\u0000\"!\u0001\u0000\u0000\u0000\"#\u0001\u0000\u0000"+
		"\u0000#%\u0001\u0000\u0000\u0000$&\u0005\u0005\u0000\u0000%$\u0001\u0000"+
		"\u0000\u0000%&\u0001\u0000\u0000\u0000&\u0005\u0001\u0000\u0000\u0000"+
		"\'(\u0003\f\u0006\u0000(*\u0005\u0003\u0000\u0000)+\u0003\f\u0006\u0000"+
		"*)\u0001\u0000\u0000\u0000*+\u0001\u0000\u0000\u0000+-\u0001\u0000\u0000"+
		"\u0000,.\u0003\n\u0005\u0000-,\u0001\u0000\u0000\u0000-.\u0001\u0000\u0000"+
		"\u0000.0\u0001\u0000\u0000\u0000/1\u0005\u0005\u0000\u00000/\u0001\u0000"+
		"\u0000\u000001\u0001\u0000\u0000\u00001\u0007\u0001\u0000\u0000\u0000"+
		"24\u0003\f\u0006\u000032\u0001\u0000\u0000\u000034\u0001\u0000\u0000\u0000"+
		"45\u0001\u0000\u0000\u000057\u0005\u0004\u0000\u000068\u0003\f\u0006\u0000"+
		"76\u0001\u0000\u0000\u000078\u0001\u0000\u0000\u00008:\u0001\u0000\u0000"+
		"\u00009;\u0005\u0005\u0000\u0000:9\u0001\u0000\u0000\u0000:;\u0001\u0000"+
		"\u0000\u0000;\t\u0001\u0000\u0000\u0000<>\u0005\u0004\u0000\u0000=?\u0003"+
		"\f\u0006\u0000>=\u0001\u0000\u0000\u0000>?\u0001\u0000\u0000\u0000?\u000b"+
		"\u0001\u0000\u0000\u0000@B\u0005\u0006\u0000\u0000A@\u0001\u0000\u0000"+
		"\u0000BC\u0001\u0000\u0000\u0000CA\u0001\u0000\u0000\u0000CD\u0001\u0000"+
		"\u0000\u0000D\r\u0001\u0000\u0000\u0000\r\u0011\u001a\u001e\"%*-037:>"+
		"C";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}