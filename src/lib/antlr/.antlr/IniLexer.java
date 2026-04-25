// Generated from /home/jochen/workdir/YAIP/src/lib/antlr/IniLexer.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class IniLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		LBRACK=1, RBRACK=2, EQUAL=3, SEMI=4, NL=5, TEXT=6;
	public static final int
		VALUE_MODE=1;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE", "VALUE_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"LBRACK", "RBRACK", "EQUAL", "SEMI", "NL", "TEXT", "VALUE_SEMI", "VALUE_NL", 
			"VALUE_TEXT"
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


	public IniLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "IniLexer.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\u0004\u0000\u0006<\u0006\uffff\uffff\u0006\uffff\uffff\u0002\u0000\u0007"+
		"\u0000\u0002\u0001\u0007\u0001\u0002\u0002\u0007\u0002\u0002\u0003\u0007"+
		"\u0003\u0002\u0004\u0007\u0004\u0002\u0005\u0007\u0005\u0002\u0006\u0007"+
		"\u0006\u0002\u0007\u0007\u0007\u0002\b\u0007\b\u0001\u0000\u0001\u0000"+
		"\u0001\u0001\u0001\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002"+
		"\u0001\u0003\u0001\u0003\u0001\u0004\u0003\u0004 \b\u0004\u0001\u0004"+
		"\u0001\u0004\u0001\u0005\u0004\u0005%\b\u0005\u000b\u0005\f\u0005&\u0001"+
		"\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0007\u0003"+
		"\u0007/\b\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001"+
		"\u0007\u0001\b\u0004\b7\b\b\u000b\b\f\b8\u0001\b\u0001\b\u0000\u0000\t"+
		"\u0002\u0001\u0004\u0002\u0006\u0003\b\u0004\n\u0005\f\u0006\u000e\u0000"+
		"\u0010\u0000\u0012\u0000\u0002\u0000\u0001\u0002\u0006\u0000\n\n\r\r;"+
		";==[[]]\u0003\u0000\n\n\r\r;;>\u0000\u0002\u0001\u0000\u0000\u0000\u0000"+
		"\u0004\u0001\u0000\u0000\u0000\u0000\u0006\u0001\u0000\u0000\u0000\u0000"+
		"\b\u0001\u0000\u0000\u0000\u0000\n\u0001\u0000\u0000\u0000\u0000\f\u0001"+
		"\u0000\u0000\u0000\u0001\u000e\u0001\u0000\u0000\u0000\u0001\u0010\u0001"+
		"\u0000\u0000\u0000\u0001\u0012\u0001\u0000\u0000\u0000\u0002\u0014\u0001"+
		"\u0000\u0000\u0000\u0004\u0016\u0001\u0000\u0000\u0000\u0006\u0018\u0001"+
		"\u0000\u0000\u0000\b\u001c\u0001\u0000\u0000\u0000\n\u001f\u0001\u0000"+
		"\u0000\u0000\f$\u0001\u0000\u0000\u0000\u000e(\u0001\u0000\u0000\u0000"+
		"\u0010.\u0001\u0000\u0000\u0000\u00126\u0001\u0000\u0000\u0000\u0014\u0015"+
		"\u0005[\u0000\u0000\u0015\u0003\u0001\u0000\u0000\u0000\u0016\u0017\u0005"+
		"]\u0000\u0000\u0017\u0005\u0001\u0000\u0000\u0000\u0018\u0019\u0005=\u0000"+
		"\u0000\u0019\u001a\u0001\u0000\u0000\u0000\u001a\u001b\u0006\u0002\u0000"+
		"\u0000\u001b\u0007\u0001\u0000\u0000\u0000\u001c\u001d\u0005;\u0000\u0000"+
		"\u001d\t\u0001\u0000\u0000\u0000\u001e \u0005\r\u0000\u0000\u001f\u001e"+
		"\u0001\u0000\u0000\u0000\u001f \u0001\u0000\u0000\u0000 !\u0001\u0000"+
		"\u0000\u0000!\"\u0005\n\u0000\u0000\"\u000b\u0001\u0000\u0000\u0000#%"+
		"\b\u0000\u0000\u0000$#\u0001\u0000\u0000\u0000%&\u0001\u0000\u0000\u0000"+
		"&$\u0001\u0000\u0000\u0000&\'\u0001\u0000\u0000\u0000\'\r\u0001\u0000"+
		"\u0000\u0000()\u0005;\u0000\u0000)*\u0001\u0000\u0000\u0000*+\u0006\u0006"+
		"\u0001\u0000+,\u0006\u0006\u0002\u0000,\u000f\u0001\u0000\u0000\u0000"+
		"-/\u0005\r\u0000\u0000.-\u0001\u0000\u0000\u0000./\u0001\u0000\u0000\u0000"+
		"/0\u0001\u0000\u0000\u000001\u0005\n\u0000\u000012\u0001\u0000\u0000\u0000"+
		"23\u0006\u0007\u0003\u000034\u0006\u0007\u0002\u00004\u0011\u0001\u0000"+
		"\u0000\u000057\b\u0001\u0000\u000065\u0001\u0000\u0000\u000078\u0001\u0000"+
		"\u0000\u000086\u0001\u0000\u0000\u000089\u0001\u0000\u0000\u00009:\u0001"+
		"\u0000\u0000\u0000:;\u0006\b\u0004\u0000;\u0013\u0001\u0000\u0000\u0000"+
		"\u0006\u0000\u0001\u001f&.8\u0005\u0005\u0001\u0000\u0007\u0004\u0000"+
		"\u0004\u0000\u0000\u0007\u0005\u0000\u0007\u0006\u0000";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}