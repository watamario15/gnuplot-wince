/*
 * $Id: canvasmath.js,v 1.5 2009/03/05 07:01:21 sfeam Exp $
 */
// The canvastext.js code was released to the public domain by Jim Studt, 2007.
// He may keep some sort of up to date copy at http://www.federated.com/~jim/canvastext/
// Mar 2009 Ethan A Merritt (EAM) Modify code to work in non-ascii environments.
//	    Add Latin-1, Hershey simplex Greek, and math symbols with unicode indexing.
//
var CanvasTextFunctions = { };

CanvasTextFunctions.letters = {
    ' ': { width: 16, points: [] },
    '!': { width: 10, points: [[5,21],[5,7],[-1,-1],[5,2],[4,1],[5,0],[6,1],[5,2]] },
    '"': { width: 16, points: [[4,21],[4,14],[-1,-1],[12,21],[12,14]] },
    '#': { width: 21, points: [[11,25],[4,-7],[-1,-1],[17,25],[10,-7],[-1,-1],[4,12],[18,12],[-1,-1],[3,6],[17,6]] },
    '$': { width: 20, points: [[8,25],[8,-4],[-1,-1],[12,25],[12,-4],[-1,-1],[17,18],[15,20],[12,21],[8,21],[5,20],[3,18],[3,16],[4,14],[5,13],[7,12],[13,10],[15,9],[16,8],[17,6],[17,3],[15,1],[12,0],[8,0],[5,1],[3,3]] },
    '%': { width: 24, points: [[21,21],[3,0],[-1,-1],[8,21],[10,19],[10,17],[9,15],[7,14],[5,14],[3,16],[3,18],[4,20],[6,21],[8,21],[10,20],[13,19],[16,19],[19,20],[21,21],[-1,-1],[17,7],[15,6],[14,4],[14,2],[16,0],[18,0],[20,1],[21,3],[21,5],[19,7],[17,7]] },
    '&': { width: 26, points: [[23,12],[23,13],[22,14],[21,14],[20,13],[19,11],[17,6],[15,3],[13,1],[11,0],[7,0],[5,1],[4,2],[3,4],[3,6],[4,8],[5,9],[12,13],[13,14],[14,16],[14,18],[13,20],[11,21],[9,20],[8,18],[8,16],[9,13],[11,10],[16,3],[18,1],[20,0],[22,0],[23,1],[23,2]] },
    '\'': { width: 10, points: [[5,19],[4,20],[5,21],[6,20],[6,18],[5,16],[4,15]] },
    '(': { width: 14, points: [[11,25],[9,23],[7,20],[5,16],[4,11],[4,7],[5,2],[7,-2],[9,-5],[11,-7]] },
    ')': { width: 14, points: [[3,25],[5,23],[7,20],[9,16],[10,11],[10,7],[9,2],[7,-2],[5,-5],[3,-7]] },
    '*': { width: 16, points: [[8,21],[8,9],[-1,-1],[3,18],[13,12],[-1,-1],[13,18],[3,12]] },
    '+': { width: 20, points: [[10,15],[10,3],[-1,-1],[4,9],[16,9]] },
    ',': { width: 10, points: [[6,1],[5,0],[4,1],[5,2],[6,1],[6,-1],[5,-3],[4,-4]] },
    '-': { width: 20, points: [[4,9],[16,9]] },
    '.': { width: 10, points: [[5,2],[4,1],[5,0],[6,1],[5,2]] },
    '/': { width: 20, points: [[19,25],[1,-7]] },
    '0': { width: 20, points: [[9,21],[6,20],[4,17],[3,12],[3,9],[4,4],[6,1],[9,0],[11,0],[14,1],[16,4],[17,9],[17,12],[16,17],[14,20],[11,21],[9,21]] },
    '1': { width: 20, points: [[6,17],[8,18],[11,21],[11,0]] },
    '2': { width: 20, points: [[4,16],[4,17],[5,19],[6,20],[8,21],[12,21],[14,20],[15,19],[16,17],[16,15],[15,13],[13,10],[3,0],[17,0]] },
    '3': { width: 20, points: [[5,21],[16,21],[10,13],[13,13],[15,12],[16,11],[17,8],[17,6],[16,3],[14,1],[11,0],[8,0],[5,1],[4,2],[3,4]] },
    '4': { width: 20, points: [[13,21],[3,7],[18,7],[-1,-1],[13,21],[13,0]] },
    '5': { width: 20, points: [[15,21],[5,21],[4,12],[5,13],[8,14],[11,14],[14,13],[16,11],[17,8],[17,6],[16,3],[14,1],[11,0],[8,0],[5,1],[4,2],[3,4]] },
    '6': { width: 20, points: [[16,18],[15,20],[12,21],[10,21],[7,20],[5,17],[4,12],[4,7],[5,3],[7,1],[10,0],[11,0],[14,1],[16,3],[17,6],[17,7],[16,10],[14,12],[11,13],[10,13],[7,12],[5,10],[4,7]] },
    '7': { width: 20, points: [[17,21],[7,0],[-1,-1],[3,21],[17,21]] },
    '8': { width: 20, points: [[8,21],[5,20],[4,18],[4,16],[5,14],[7,13],[11,12],[14,11],[16,9],[17,7],[17,4],[16,2],[15,1],[12,0],[8,0],[5,1],[4,2],[3,4],[3,7],[4,9],[6,11],[9,12],[13,13],[15,14],[16,16],[16,18],[15,20],[12,21],[8,21]] },
    '9': { width: 20, points: [[16,14],[15,11],[13,9],[10,8],[9,8],[6,9],[4,11],[3,14],[3,15],[4,18],[6,20],[9,21],[10,21],[13,20],[15,18],[16,14],[16,9],[15,4],[13,1],[10,0],[8,0],[5,1],[4,3]] },
    ':': { width: 10, points: [[5,14],[4,13],[5,12],[6,13],[5,14],[-1,-1],[5,2],[4,1],[5,0],[6,1],[5,2]] },
    ';': { width: 10, points: [[5,14],[4,13],[5,12],[6,13],[5,14],[-1,-1],[6,1],[5,0],[4,1],[5,2],[6,1],[6,-1],[5,-3],[4,-4]] },
    '<': { width: 24, points: [[20,18],[4,9],[20,0]] },
    '=': { width: 24, points: [[3,12],[20,12],[-1,-1],[3,6],[20,6]] },
    '>': { width: 24, points: [[4,18],[20,9],[4,0]] },
    '?': { width: 18, points: [[3,16],[3,17],[4,19],[5,20],[7,21],[11,21],[13,20],[14,19],[15,17],[15,15],[14,13],[13,12],[9,10],[9,7],[-1,-1],[9,2],[8,1],[9,0],[10,1],[9,2]] },
    '@': { width: 27, points: [[18,13],[17,15],[15,16],[12,16],[10,15],[9,14],[8,11],[8,8],[9,6],[11,5],[14,5],[16,6],[17,8],[-1,-1],[12,16],[10,14],[9,11],[9,8],[10,6],[11,5],[-1,-1],[18,16],[17,8],[17,6],[19,5],[21,5],[23,7],[24,10],[24,12],[23,15],[22,17],[20,19],[18,20],[15,21],[12,21],[9,20],[7,19],[5,17],[4,15],[3,12],[3,9],[4,6],[5,4],[7,2],[9,1],[12,0],[15,0],[18,1],[20,2],[21,3],[-1,-1],[19,16],[18,8],[18,6],[19,5]] },
    'A': { width: 18, points: [[9,21],[1,0],[-1,-1],[9,21],[17,0],[-1,-1],[4,7],[14,7]] },
    'B': { width: 21, points: [[4,21],[4,0],[-1,-1],[4,21],[13,21],[16,20],[17,19],[18,17],[18,15],[17,13],[16,12],[13,11],[-1,-1],[4,11],[13,11],[16,10],[17,9],[18,7],[18,4],[17,2],[16,1],[13,0],[4,0]] },
    'C': { width: 21, points: [[18,16],[17,18],[15,20],[13,21],[9,21],[7,20],[5,18],[4,16],[3,13],[3,8],[4,5],[5,3],[7,1],[9,0],[13,0],[15,1],[17,3],[18,5]] },
    'D': { width: 21, points: [[4,21],[4,0],[-1,-1],[4,21],[11,21],[14,20],[16,18],[17,16],[18,13],[18,8],[17,5],[16,3],[14,1],[11,0],[4,0]] },
    'E': { width: 19, points: [[4,21],[4,0],[-1,-1],[4,21],[17,21],[-1,-1],[4,11],[12,11],[-1,-1],[4,0],[17,0]] },
    'F': { width: 18, points: [[4,21],[4,0],[-1,-1],[4,21],[17,21],[-1,-1],[4,11],[12,11]] },
    'G': { width: 21, points: [[18,16],[17,18],[15,20],[13,21],[9,21],[7,20],[5,18],[4,16],[3,13],[3,8],[4,5],[5,3],[7,1],[9,0],[13,0],[15,1],[17,3],[18,5],[18,8],[-1,-1],[13,8],[18,8]] },
    'H': { width: 22, points: [[4,21],[4,0],[-1,-1],[18,21],[18,0],[-1,-1],[4,11],[18,11]] },
    'I': { width: 8, points: [[4,21],[4,0]] },
    'J': { width: 16, points: [[12,21],[12,5],[11,2],[10,1],[8,0],[6,0],[4,1],[3,2],[2,5],[2,7]] },
    'K': { width: 21, points: [[4,21],[4,0],[-1,-1],[18,21],[4,7],[-1,-1],[9,12],[18,0]] },
    'L': { width: 17, points: [[4,21],[4,0],[-1,-1],[4,0],[16,0]] },
    'M': { width: 24, points: [[4,21],[4,0],[-1,-1],[4,21],[12,0],[-1,-1],[20,21],[12,0],[-1,-1],[20,21],[20,0]] },
    'N': { width: 22, points: [[4,21],[4,0],[-1,-1],[4,21],[18,0],[-1,-1],[18,21],[18,0]] },
    'O': { width: 22, points: [[9,21],[7,20],[5,18],[4,16],[3,13],[3,8],[4,5],[5,3],[7,1],[9,0],[13,0],[15,1],[17,3],[18,5],[19,8],[19,13],[18,16],[17,18],[15,20],[13,21],[9,21]] },
    'P': { width: 21, points: [[4,21],[4,0],[-1,-1],[4,21],[13,21],[16,20],[17,19],[18,17],[18,14],[17,12],[16,11],[13,10],[4,10]] },
    'Q': { width: 22, points: [[9,21],[7,20],[5,18],[4,16],[3,13],[3,8],[4,5],[5,3],[7,1],[9,0],[13,0],[15,1],[17,3],[18,5],[19,8],[19,13],[18,16],[17,18],[15,20],[13,21],[9,21],[-1,-1],[12,4],[18,-2]] },
    'R': { width: 21, points: [[4,21],[4,0],[-1,-1],[4,21],[13,21],[16,20],[17,19],[18,17],[18,15],[17,13],[16,12],[13,11],[4,11],[-1,-1],[11,11],[18,0]] },
    'S': { width: 20, points: [[17,18],[15,20],[12,21],[8,21],[5,20],[3,18],[3,16],[4,14],[5,13],[7,12],[13,10],[15,9],[16,8],[17,6],[17,3],[15,1],[12,0],[8,0],[5,1],[3,3]] },
    'T': { width: 16, points: [[8,21],[8,0],[-1,-1],[1,21],[15,21]] },
    'U': { width: 22, points: [[4,21],[4,6],[5,3],[7,1],[10,0],[12,0],[15,1],[17,3],[18,6],[18,21]] },
    'V': { width: 18, points: [[1,21],[9,0],[-1,-1],[17,21],[9,0]] },
    'W': { width: 24, points: [[2,21],[7,0],[-1,-1],[12,21],[7,0],[-1,-1],[12,21],[17,0],[-1,-1],[22,21],[17,0]] },
    'X': { width: 20, points: [[3,21],[17,0],[-1,-1],[17,21],[3,0]] },
    'Y': { width: 18, points: [[1,21],[9,11],[9,0],[-1,-1],[17,21],[9,11]] },
    'Z': { width: 20, points: [[17,21],[3,0],[-1,-1],[3,21],[17,21],[-1,-1],[3,0],[17,0]] },
    '[': { width: 14, points: [[4,25],[4,-7],[-1,-1],[5,25],[5,-7],[-1,-1],[4,25],[11,25],[-1,-1],[4,-7],[11,-7]] },
    '\\': { width: 14, points: [[0,21],[14,-3]] },
    ']': { width: 14, points: [[9,25],[9,-7],[-1,-1],[10,25],[10,-7],[-1,-1],[3,25],[10,25],[-1,-1],[3,-7],[10,-7]] },
    '^': { width: 16, points: [[5,15],[8,19],[11,15],[-1,-1],[2,12],[8,18],[14,12]] },
    '_': { width: 16, points: [[0,-2],[16,-2]] },
    '`': { width: 10, points: [[6,21],[5,20],[4,18],[4,16],[5,15],[6,16],[5,17]] },
    'a': { width: 19, points: [[15,14],[15,0],[-1,-1],[15,11],[13,13],[11,14],[8,14],[6,13],[4,11],[3,8],[3,6],[4,3],[6,1],[8,0],[11,0],[13,1],[15,3]] },
    'b': { width: 19, points: [[4,21],[4,0],[-1,-1],[4,11],[6,13],[8,14],[11,14],[13,13],[15,11],[16,8],[16,6],[15,3],[13,1],[11,0],[8,0],[6,1],[4,3]] },
    'c': { width: 18, points: [[15,11],[13,13],[11,14],[8,14],[6,13],[4,11],[3,8],[3,6],[4,3],[6,1],[8,0],[11,0],[13,1],[15,3]] },
    'd': { width: 19, points: [[15,21],[15,0],[-1,-1],[15,11],[13,13],[11,14],[8,14],[6,13],[4,11],[3,8],[3,6],[4,3],[6,1],[8,0],[11,0],[13,1],[15,3]] },
    'e': { width: 18, points: [[3,8],[15,8],[15,10],[14,12],[13,13],[11,14],[8,14],[6,13],[4,11],[3,8],[3,6],[4,3],[6,1],[8,0],[11,0],[13,1],[15,3]] },
    'f': { width: 12, points: [[10,21],[8,21],[6,20],[5,17],[5,0],[-1,-1],[2,14],[9,14]] },
    'g': { width: 19, points: [[15,14],[15,-2],[14,-5],[13,-6],[11,-7],[8,-7],[6,-6],[-1,-1],[15,11],[13,13],[11,14],[8,14],[6,13],[4,11],[3,8],[3,6],[4,3],[6,1],[8,0],[11,0],[13,1],[15,3]] },
    'h': { width: 19, points: [[4,21],[4,0],[-1,-1],[4,10],[7,13],[9,14],[12,14],[14,13],[15,10],[15,0]] },
    'i': { width: 8, points: [[3,21],[4,20],[5,21],[4,22],[3,21],[-1,-1],[4,14],[4,0]] },
    'j': { width: 10, points: [[5,21],[6,20],[7,21],[6,22],[5,21],[-1,-1],[6,14],[6,-3],[5,-6],[3,-7],[1,-7]] },
    'k': { width: 17, points: [[4,21],[4,0],[-1,-1],[14,14],[4,4],[-1,-1],[8,8],[15,0]] },
    'l': { width: 8, points: [[4,21],[4,0]] },
    'm': { width: 30, points: [[4,14],[4,0],[-1,-1],[4,10],[7,13],[9,14],[12,14],[14,13],[15,10],[15,0],[-1,-1],[15,10],[18,13],[20,14],[23,14],[25,13],[26,10],[26,0]] },
    'n': { width: 19, points: [[4,14],[4,0],[-1,-1],[4,10],[7,13],[9,14],[12,14],[14,13],[15,10],[15,0]] },
    'o': { width: 19, points: [[8,14],[6,13],[4,11],[3,8],[3,6],[4,3],[6,1],[8,0],[11,0],[13,1],[15,3],[16,6],[16,8],[15,11],[13,13],[11,14],[8,14]] },
    'p': { width: 19, points: [[4,14],[4,-7],[-1,-1],[4,11],[6,13],[8,14],[11,14],[13,13],[15,11],[16,8],[16,6],[15,3],[13,1],[11,0],[8,0],[6,1],[4,3]] },
    'q': { width: 19, points: [[15,14],[15,-7],[-1,-1],[15,11],[13,13],[11,14],[8,14],[6,13],[4,11],[3,8],[3,6],[4,3],[6,1],[8,0],[11,0],[13,1],[15,3]] },
    'r': { width: 13, points: [[4,14],[4,0],[-1,-1],[4,8],[5,11],[7,13],[9,14],[12,14]] },
    's': { width: 17, points: [[14,11],[13,13],[10,14],[7,14],[4,13],[3,11],[4,9],[6,8],[11,7],[13,6],[14,4],[14,3],[13,1],[10,0],[7,0],[4,1],[3,3]] },
    't': { width: 12, points: [[5,21],[5,4],[6,1],[8,0],[10,0],[-1,-1],[2,14],[9,14]] },
    'u': { width: 19, points: [[4,14],[4,4],[5,1],[7,0],[10,0],[12,1],[15,4],[-1,-1],[15,14],[15,0]] },
    'v': { width: 16, points: [[2,14],[8,0],[-1,-1],[14,14],[8,0]] },
    'w': { width: 22, points: [[3,14],[7,0],[-1,-1],[11,14],[7,0],[-1,-1],[11,14],[15,0],[-1,-1],[19,14],[15,0]] },
    'x': { width: 17, points: [[3,14],[14,0],[-1,-1],[14,14],[3,0]] },
    'y': { width: 16, points: [[2,14],[8,0],[-1,-1],[14,14],[8,0],[6,-4],[4,-6],[2,-7],[1,-7]] },
    'z': { width: 17, points: [[14,14],[3,0],[-1,-1],[3,14],[14,14],[-1,-1],[3,0],[14,0]] },
    '{': { width: 14, points: [[9,25],[7,24],[6,23],[5,21],[5,19],[6,17],[7,16],[8,14],[8,12],[6,10],[-1,-1],[7,24],[6,22],[6,20],[7,18],[8,17],[9,15],[9,13],[8,11],[4,9],[8,7],[9,5],[9,3],[8,1],[7,0],[6,-2],[6,-4],[7,-6],[-1,-1],[6,8],[8,6],[8,4],[7,2],[6,1],[5,-1],[5,-3],[6,-5],[7,-6],[9,-7]] },
    '|': { width: 8, points: [[4,25],[4,-7]] },
    '}': { width: 14, points: [[5,25],[7,24],[8,23],[9,21],[9,19],[8,17],[7,16],[6,14],[6,12],[8,10],[-1,-1],[7,24],[8,22],[8,20],[7,18],[6,17],[5,15],[5,13],[6,11],[10,9],[6,7],[5,5],[5,3],[6,1],[7,0],[8,-2],[8,-4],[7,-6],[-1,-1],[8,8],[6,6],[6,4],[7,2],[8,1],[9,-1],[9,-3],[8,-5],[7,-6],[5,-7]] },
    '~': { width: 24, points: [[3,6],[3,8],[4,11],[6,12],[8,12],[10,11],[14,8],[16,7],[18,7],[20,8],[21,10],[-1,-1],[3,8],[4,10],[6,11],[8,11],[10,10],[14,7],[16,6],[18,6],[20,7],[21,10],[21,12]] },

// latin-1 as diacritical + base character

192: { width: 0, points: [[4,28],[10,24],[-99,'A']] },
193: { width: 0, points: [[8,24],[14,28],[-99,'A']] },
194: { width: 0, points: [[5,24],[9,27],[13,24],[-99,'A']] },
195: { width: 0, points: [[4,24],[5,26],[6,27],[8,27], [10,24],[12,24],[13,25],[14,27],[-99,'A']] },
196: { width: 0, points: [[6,25],[6,26],[7,26],[7,25],[-1,-1],[12,25],[12,26],[13,26],[13,25],[-99,'A']] },
197: { width: 0, points: [[8,27],[6,25],[6,23],[8,21],[10,21],[12,23],[12,25],[10,27],[8,27],[-99,'A']]},
198: { width: 11, points: [[3,0],[14,21],[-1,-1],[7,8],[14,8],[-99,'E']] },
199: { width: 0, points: [[10,0],[10,-3],[11,-3],[12,-4],[12,-6],[11,-7],[8,-7],[-99,'C']] },
200: { width: 0, points: [[8,28],[14,24],[-99,'E']] },
201: { width: 0, points: [[6,24],[12,28],[-99,'E']] },
202: { width: 0, points: [[5,24],[9,27],[13,24],[-99,'E']] },
203: { width: 0, points: [[6,25],[6,26],[7,26],[7,25],[-1,-1],[12,25],[12,26],[13,26],[13,25],[-99,'E']] },
204: { width: 0, points: [[-99,'I']] },
205: { width: 0, points: [[-99,'I']] },
206: { width: 0, points: [[-99,'I']] },
207: { width: 0, points: [[-99,'I']] },
209: { width: 0, points: [[6,24],[7,26],[8,27],[10,27], [12,24],[14,24],[15,25],[16,27],[-99,'N']] },
210: { width: 0, points: [[8,28],[14,24],[-99,'O']] },
211: { width: 0, points: [[6,24],[12,28],[-99,'O']] },
212: { width: 0, points: [[7,24],[11,27],[15,24],[-99,'O']] },
213: { width: 0, points: [[6,24],[7,26],[8,27],[10,27], [12,24],[14,24],[15,25],[16,27],[-99,'O']] },
214: { width: 0, points: [[8,25],[8,26],[9,26],[9,25],[-1,-1],[14,25],[14,26],[15,26],[15,25],[-99,'O']] },
216: { width: 0, points: [[3,0],[19,21],[-99,'O']] },
217: { width: 0, points: [[8,28],[14,24],[-99,'U']] },
218: { width: 0, points: [[6,24],[12,28],[-99,'U']] },
219: { width: 0, points: [[7,24],[11,27],[15,24],[-99,'U']] },
220: { width: 0, points: [[8,25],[8,26],[9,26],[9,25],[-1,-1],[14,25],[14,26],[15,26],[15,25],[-99,'U']] },
224: { width: 0, points: [[8,21],[14,17],[-99,'a']] },
225: { width: 0, points: [[6,17],[12,21],[-99,'a']] },
226: { width: 0, points: [[5,17],[9,20],[13,17],[-99,'a']] },
227: { width: 0, points: [[4,17],[5,19],[6,20],[8,20], [10,17],[12,17],[13,18],[14,20],[-99,'a']] },
228: { width: 0, points: [[6,18],[6,19],[7,19],[7,18],[-1,-1],[12,18],[12,19],[13,19],[13,18],[-99,'a']] },
229: { width: 0, points: [[9,21],[7,19],[7,18],[9,16],[10,16],[12,18],[12,19],[10,21],[8,21],[-99,'a']] },
231: { width: 0, points: [[10,0],[10,-3],[11,-3],[12,-4],[12,-6],[11,-7],[8,-7],[-99,'c']] },
232: { width: 0, points: [[8,21],[14,17],[-99,'e']] },
233: { width: 0, points: [[6,17],[12,21],[-99,'e']] },
234: { width: 0, points: [[5,17],[9,20],[13,17],[-99,'e']] },
235: { width: 0, points: [[6,18],[6,19],[7,19],[7,18],[-1,-1],[12,18],[12,19],[13,19],[13,18],[-99,'e']] },
236: { width: 8, points: [[4,14],[4,0],[-1,-1],[1,21],[4,18]] },
237: { width: 8, points: [[4,14],[4,0],[-1,-1],[7,21],[4,18]] },
238: { width: 8, points: [[4,14],[4,0],[-1,-1],[1,17],[4,20],[7,17]] },
239: { width: 10, points: [[5,14],[5,0],[-1,-1],[2,18],[2,19],[3,19],[3,18],[-1,-1],[7,18],[7,19],[8,19],[8,18]] },
241: { width: 0, points: [[5,17],[6,19],[7,20],[9,20], [11,17],[13,17],[14,18],[15,20],[-99,'n']] },
242: { width: 0, points: [[8,21],[14,17],[-99,'o']] },
243: { width: 0, points: [[6,17],[12,21],[-99,'o']] },
244: { width: 0, points: [[5,17],[9,20],[13,17],[-99,'o']] },
245: { width: 0, points: [[4,17],[5,19],[6,20],[8,20], [10,17],[12,17],[13,18],[14,20],[-99,'o']] },
246: { width: 0, points: [[6,18],[6,19],[7,19],[7,18],[-1,-1],[12,18],[12,19],[13,19],[13,18],[-99,'o']] },
247: { width: 20, points: [[4,9],[16,9],[-1,-1],[10,14],[10,13],[11,13],[11,14],[-1,-1],[10,4],[10,5],[11,5],[11,4]] },
248: { width: 0, points: [[3,0],[17,14],[-99,'o']] },
249: { width: 0, points: [[8,21],[14,17],[-99,'u']] },
250: { width: 0, points: [[6,17],[12,21],[-99,'u']] },
251: { width: 0, points: [[5,17],[9,20],[13,17],[-99,'u']] },
252: { width: 0, points: [[6,18],[6,19],[7,19],[7,18],[-1,-1],[12,18],[12,19],[13,19],[13,18],[-99,'u']] },
253: { width: 0, points: [[12,21],[6,17],[-99,'y']] },
255: { width: 0, points: [[6,18],[6,19],[7,19],[7,18],[-1,-1],[12,18],[12,19],[13,19],[13,18],[-99,'y']] },

// Hershey simplex greek font

913: { width: 18, points: [[9,22],[1,1],[-1,-1],[9,22],[17,1],[-1,-1],[4,8],[14,8]] },
914: { width: 21, points: [[4,22],[4,1],[-1,-1],[4,22],[13,22],[16,21],[17,20],[18,18],[18,16],[17,14],[16,13],[13,12],[-1,-1],[4,12],[13,12],[16,11],[17,10],[18,8],[18,5],[17,3],[16,2],[13,1],[4,1]] },
915: { width: 17, points: [[4,22],[4,1],[-1,-1],[4,22],[16,22]] },
916: { width: 18, points: [[9,22],[1,1],[-1,-1],[9,22],[17,1],[-1,-1],[1,1],[17,1]] },
917: { width: 19, points: [[4,22],[4,1],[-1,-1],[4,22],[17,22],[-1,-1],[4,12],[12,12],[-1,-1],[4,1],[17,1]] },
918: { width: 20, points: [[17,22],[3,1],[-1,-1],[3,22],[17,22],[-1,-1],[3,1],[17,1]] },
919: { width: 22, points: [[4,22],[4,1],[-1,-1],[18,22],[18,1],[-1,-1],[4,12],[18,12]] },
920: { width: 22, points: [[9,22],[7,21],[5,19],[4,17],[3,14],[3,9],[4,6],[5,4],[7,2],[9,1],[13,1],[15,2],[17,4],[18,6],[19,9],[19,14],[18,17],[17,19],[15,21],[13,22],[9,22],[-1,-1],[8,12],[14,12]] },
921: { width:  8, points: [[4,22],[4,1]] },
922: { width: 21, points: [[4,22],[4,1],[-1,-1],[18,22],[4,8],[-1,-1],[9,13],[18,1]] },
923: { width: 18, points: [[9,22],[1,1],[-1,-1],[9,22],[17,1]] },
924: { width: 24, points: [[4,22],[4,1],[-1,-1],[4,22],[12,1],[-1,-1],[20,22],[12,1],[-1,-1],[20,22],[20,1]] },
925: { width: 22, points: [[4,22],[4,1],[-1,-1],[4,22],[18,1],[-1,-1],[18,22],[18,1]] },
926: { width: 18, points: [[2,22],[16,22],[-1,-1],[6,12],[12,12],[-1,-1],[2,1],[16,1]] },
927: { width: 22, points: [[9,22],[7,21],[5,19],[4,17],[3,14],[3,9],[4,6],[5,4],[7,2],[9,1],[13,1],[15,2],[17,4],[18,6],[19,9],[19,14],[18,17],[17,19],[15,21],[13,22],[9,22]] },
928: { width: 22, points: [[4,22],[4,1],[-1,-1],[18,22],[18,1],[-1,-1],[4,22],[18,22]] },
929: { width: 21, points: [[4,22],[4,1],[-1,-1],[4,22],[13,22],[16,21],[17,20],[18,18],[18,15],[17,13],[16,12],[13,11],[4,11]] },
931: { width: 18, points: [[2,22],[9,12],[2,1],[-1,-1],[2,22],[16,22],[-1,-1],[2,1],[16,1]] },
932: { width: 16, points: [[8,22],[8,1],[-1,-1],[1,22],[15,22]] },
933: { width: 18, points: [[2,17],[2,19],[3,21],[4,22],[6,22],[7,21],[8,19],[9,15],[9,1],[-1,-1],[16,17],[16,19],[15,21],[14,22],[12,22],[11,21],[10,19],[9,15]] },
934: { width: 20, points: [[10,22],[10,1],[-1,-1],[8,17],[5,16],[4,15],[3,13],[3,10],[4,8],[5,7],[8,6],[12,6],[15,7],[16,8],[17,10],[17,13],[16,15],[15,16],[12,17],[8,17]] },
935: { width: 20, points: [[3,22],[17,1],[-1,-1],[3,1],[17,22]] },
936: { width: 22, points: [[11,22],[11,1],[-1,-1],[2,16],[3,16],[4,15],[5,11],[6,9],[7,8],[10,7],[12,7],[15,8],[16,9],[17,11],[18,15],[19,16],[20,16]] },
937: { width: 20, points: [[3,1],[7,1],[4,8],[3,12],[3,16],[4,19],[6,21],[9,22],[11,22],[14,21],[16,19],[17,16],[17,12],[16,8],[13,1],[17,1]] },
945: { width: 21, points: [[9,15],[7,14],[5,12],[4,10],[3,7],[3,4],[4,2],[6,1],[8,1],[10,2],[13,5],[15,8],[17,12],[18,15],[-1,-1],[9,15],[11,15],[12,14],[13,12],[15,4],[16,2],[17,1],[18,1]] },
946: { width: 19, points: [[12,22],[10,21],[8,19],[6,15],[5,12],[4,8],[3,2],[2,-6],[-1,-1],[12,22],[14,22],[16,20],[16,17],[15,15],[14,14],[12,13],[9,13],[-1,-1],[9,13],[11,12],[13,10],[14,8],[14,5],[13,3],[12,2],[10,1],[8,1],[6,2],[5,3],[4,6]] },
947: { width: 19, points: [[1,12],[3,14],[5,15],[6,15],[8,14],[9,13],[10,10],[10,6],[9,1],[-1,-1],[17,15],[16,12],[15,10],[9,1],[7,-3],[6,-6]] },
948: { width: 18, points: [[11,15],[8,15],[6,14],[4,12],[3,9],[3,6],[4,3],[5,2],[7,1],[9,1],[11,2],[13,4],[14,7],[14,10],[13,13],[11,15],[9,17],[8,19],[8,21],[9,22],[11,22],[13,21],[15,19]] },
949: { width: 16, points: [[13,13],[12,14],[10,15],[7,15],[5,14],[5,12],[6,10],[9,9],[-1,-1],[9,9],[5,8],[3,6],[3,4],[4,2],[6,1],[9,1],[11,2],[13,4]] },
950: { width: 15, points: [[10,22],[8,21],[7,20],[7,19],[8,18],[11,17],[14,17],[-1,-1],[14,17],[10,15],[7,13],[4,10],[3,7],[3,5],[4,3],[6,1],[9,-1],[10,-3],[10,-5],[9,-6],[7,-6],[6,-4]] },
951: { width: 20, points: [[1,11],[2,13],[4,15],[6,15],[7,14],[7,12],[6,8],[4,1],[-1,-1],[6,8],[8,12],[10,14],[12,15],[14,15],[16,13],[16,10],[15,5],[12,-6]] },
952: { width: 17, points: [[10,22],[8,21],[6,18],[5,16],[4,13],[3,8],[3,4],[4,2],[5,1],[7,1],[9,2],[11,5],[12,7],[13,10],[14,15],[14,19],[13,21],[12,22],[10,22],[-1,-1],[4,12],[13,12]] },
953: { width: 11, points: [[6,15],[4,8],[3,4],[3,2],[4,1],[6,1],[8,3],[9,5]] },
954: { width: 18, points: [[6,15],[2,1],[-1,-1],[16,14],[15,15],[14,15],[12,14],[8,10],[6,9],[5,9],[-1,-1],[5,9],[7,8],[8,7],[10,2],[11,1],[12,1],[13,2]] },
955: { width: 16, points: [[1,22],[3,22],[5,21],[6,20],[14,1],[-1,-1],[8,15],[2,1]] },
956: { width: 21, points: [[7,15],[1,-6],[-1,-1],[6,11],[5,6],[5,3],[7,1],[9,1],[11,2],[13,4],[15,8],[-1,-1],[17,15],[15,8],[14,4],[14,2],[15,1],[17,1],[19,3],[20,5]] },
957: { width: 18, points: [[3,15],[6,15],[5,9],[4,4],[3,1],[-1,-1],[16,15],[15,12],[14,10],[12,7],[9,4],[6,2],[3,1]] },
958: { width: 16, points: [[10,22],[8,21],[7,20],[7,19],[8,18],[11,17],[14,17],[-1,-1],[11,17],[8,16],[6,15],[5,13],[5,11],[7,9],[10,8],[12,8],[-1,-1],[10,8],[6,7],[4,6],[3,4],[3,2],[5,0],[9,-2],[10,-3],[10,-5],[8,-6],[6,-6]] },
959: { width: 17, points: [[8,15],[6,14],[4,12],[3,9],[3,6],[4,3],[5,2],[7,1],[9,1],[11,2],[13,4],[14,7],[14,10],[13,13],[12,14],[10,15],[8,15]] },
960: { width: 18, points: [[6,15],[2,1],[-1,-1],[16,14],[15,15],[14,15],[12,14],[8,10],[6,9],[5,9],[-1,-1],[5,9],[7,8],[8,7],[10,2],[11,1],[12,1],[13,2]] },
960: { width: 22, points: [[9,15],[5,1],[-1,-1],[14,15],[15,9],[16,4],[17,1],[-1,-1],[2,12],[4,14],[7,15],[20,15]] },
961: { width: 18, points: [[4,9],[4,6],[5,3],[6,2],[8,1],[10,1],[12,2],[14,4],[15,7],[15,10],[14,13],[13,14],[11,15],[9,15],[7,14],[5,12],[4,9],[0,-6]] },
962: { width: 18, points: [[15,13],[14,14],[11,15],[8,15],[5,14],[4,13],[3,11],[3,9],[4,7],[6,5],[10,2],[11,0],[11,-2],[10,-3],[8,-3]] },
963: { width: 18, points: [[3,15],[6,15],[5,9],[4,4],[3,1],[-1,-1],[16,15],[15,12],[14,10],[12,7],[9,4],[6,2],[3,1]] },
963: { width: 20, points: [[18,15],[8,15],[6,14],[4,12],[3,9],[3,6],[4,3],[5,2],[7,1],[9,1],[11,2],[13,4],[14,7],[14,10],[13,13],[12,14],[10,15]] },
964: { width: 20, points: [[11,15],[8,1],[-1,-1],[2,12],[4,14],[7,15],[18,15]] },
965: { width: 20, points: [[1,11],[2,13],[4,15],[6,15],[7,14],[7,12],[5,6],[5,3],[7,1],[9,1],[12,2],[14,4],[16,8],[17,12],[17,15]] },
966: { width: 22, points: [[8,14],[6,13],[4,11],[3,8],[3,5],[4,3],[5,2],[7,1],[10,1],[13,2],[16,4],[18,7],[19,10],[19,13],[17,15],[15,15],[13,13],[11,9],[9,4],[6,-6]] },
967: { width: 18, points: [[2,15],[4,15],[6,13],[12,-4],[14,-6],[16,-6],[-1,-1],[17,15],[16,13],[14,10],[4,-1],[2,-4],[1,-6]] },
968: { width: 23, points: [[16,22],[8,-6],[-1,-1],[1,11],[2,13],[4,15],[6,15],[7,14],[7,12],[6,7],[6,4],[7,2],[9,1],[11,1],[14,2],[16,4],[18,7],[20,12],[21,15]] },
969: { width: 23, points: [[8,15],[6,14],[4,11],[3,8],[3,5],[4,2],[5,1],[7,1],[9,2],[11,5],[-1,-1],[12,9],[11,5],[12,2],[13,1],[15,1],[17,2],[19,5],[20,8],[20,11],[19,14],[18,15]] },
977: { width: 21, points: [[1,11],[2,13],[4,15],[6,15],[7,14],[7,12],[6,7],[6,4],[7,2],[8,1],[10,1],[12,2],[14,5],[15,7],[16,10],[17,15],[17,18],[16,21],[14,22],[12,22],[11,20],[11,18],[12,15],[14,12],[16,10],[19,8]] },
981: { width: 20, points: [[14,22],[6,-6],[-1,-1],[9,15],[6,14],[4,12],[3,9],[3,6],[4,4],[6,2],[9,1],[11,1],[14,2],[16,4],[17,7],[17,10],[16,12],[14,14],[11,15],[9,15]] },
982: { width: 23, points: [[9,14],[6,13],[4,11],[3,8],[3,5],[4,2],[5,1],[7,1],[9,2],[11,5],[-1,-1],[12,9],[11,5],[12,2],[13,1],[15,1],[17,2],[19,5],[20,8],[20,11],[19,14],[18,15],[-1,-1],[2,14],[4,15],[20,15]] },
986: { width: 18, points: [[15,13],[14,14],[11,15],[8,15],[5,14],[4,13],[3,11],[3,9],[4,7],[6,5],[10,2],[11,0],[11,-2],[10,-3],[8,-3]] },

// Hershey math symbols

8501: { width: 20, points: [[3,19],[4,17],[16,5],[17,3],[17,1],[-1,-1],[4,16],[16,4],[-1,-1],[3,19],[3,17],[4,15],[16,3],[17,1],[-1,-1],[8,12],[4,8],[3,6],[3,4],[4,2],[3,1],[-1,-1],[3,6],[5,2],[-1,-1],[4,8],[4,6],[5,4],[5,2],[3,1],[-1,-1],[11,9],[16,14],[-1,-1],[14,19],[14,16],[15,14],[17,14],[17,16],[15,17],[14,19],[-1,-1],[14,19],[15,16],[17,14]] },
8592: { width: 26, points: [[7,12],[4,10],[7,8],[-1,-1],[10,15],[5,10],[10,5],[-1,-1],[5,10],[22,10]] },
8593: { width: 16, points: [[6,16],[8,19],[10,16],[-1,-1],[3,13],[8,18],[13,13],[-1,-1],[8,18],[8,1]] },
8594: { width: 26, points: [[19,12],[22,10],[19,8],[-1,-1],[16,15],[21,10],[16,5],[-1,-1],[4,10],[21,10]] },
8595: { width: 16, points: [[6,4],[8,1],[10,4],[-1,-1],[3,7],[8,2],[13,7],[-1,-1],[8,19],[8,2]] },
8706: { width: 19, points: [[15,10],[14,13],[13,14],[11,15],[9,15],[6,14],[4,11],[3,8],[3,5],[4,3],[5,2],[7,1],[9,1],[12,2],[14,4],[15,7],[16,12],[16,17],[15,20],[14,21],[12,22],[9,22],[7,21],[6,20],[6,19],[7,19],[7,20],[-1,-1],[9,15],[7,14],[5,11],[4,8],[4,4],[5,2],[-1,-1],[9,1],[11,2],[13,4],[14,7],[15,12],[15,17],[14,20],[12,22]] },
8710: { width: 20, points: [[2,1],[10,22],[-1,-1],[17,1],[10,20],[-1,-1],[18,1],[10,22],[-1,-1],[2,1],[18,1],[-1,-1],[3,2],[17,2]] },
8711: { width: 20, points: [[2,22],[10,1],[-1,-1],[3,22],[10,3],[-1,-1],[18,22],[10,1],[-1,-1],[2,22],[18,22],[-1,-1],[3,21],[17,21]] },
8712: { width: 24, points: [[20,18],[13,18],[9,17],[7,16],[5,14],[4,11],[4,9],[5,6],[7,4],[9,3],[13,2],[20,2],[-1,-1],[4,10],[16,10]] },
8713: { width: 24, points: [[20,18],[13,18],[9,17],[7,16],[5,14],[4,11],[4,9],[5,6],[7,4],[9,3],[13,2],[20,2],[-1,-1],[4,10],[16,10],[-1,-1],[18,19],[6,1]] },
8719: { width: 34, points: [[7,26],[7,-6],[-1,-1],[8,26],[8,-6],[-1,-1],[26,26],[26,-6],[-1,-1],[27,26],[27,-6],[-1,-1],[3,26],[31,26],[-1,-1],[3,-6],[12,-6],[-1,-1],[22,-6],[31,-6]] },
8721: { width: 31, points: [[5,26],[15,12],[4,-6],[-1,-1],[4,26],[14,12],[-1,-1],[3,26],[14,11],[-1,-1],[3,26],[26,26],[28,19],[25,26],[-1,-1],[5,-5],[26,-5],[-1,-1],[4,-6],[26,-6],[28,1],[25,-6]] },
8728: { width:  16, points: [[7,13],[5,11],[5,9],[7,7],[9,7],[11,9],[11,11],[9,13],[7,13]] },
8729: { width:  16, points: [[7,13],[5,11],[5,9],[7,7],[9,7],[11,9],[11,11],[9,13],[7,13],[-1,-1],[7,12],[6,11],[6,9],[7,8],[9,8],[10,9],[10,11],[9,12],[7,12],[-1,-1],[8,11],[7,10],[8,9],[9,10],[8,11]] },
8730: { width: 22, points: [[3,15],[7,15],[13,3],[-1,-1],[6,15],[13,1],[-1,-1],[22,26],[13,1]] },
8733: { width: 25, points: [[21,5],[19,5],[17,6],[15,8],[12,12],[11,13],[9,14],[7,14],[5,13],[4,11],[4,9],[5,7],[7,6],[9,6],[11,7],[12,8],[15,12],[17,14],[19,15],[21,15]] },
8734: { width: 25, points: [[22,9],[21,7],[19,6],[17,6],[15,7],[14,8],[11,12],[10,13],[8,14],[6,14],[4,13],[3,11],[3,9],[4,7],[6,6],[8,6],[10,7],[11,8],[14,12],[15,13],[17,14],[19,14],[21,13],[22,11],[22,9]] },
8745: { width: 24, points: [[4,2],[4,9],[5,13],[6,15],[8,17],[11,18],[13,18],[16,17],[18,15],[19,13],[20,9],[20,2]] },
8746: { width: 24, points: [[4,18],[4,11],[5,7],[6,5],[8,3],[11,2],[13,2],[16,3],[18,5],[19,7],[20,11],[20,18]] },
8747: { width: 24, points: [[21,25],[20,24],[21,23],[22,24],[22,25],[21,26],[19,26],[17,25],[15,23],[14,21],[13,18],[12,14],[10,2],[9,-2],[8,-4],[-1,-1],[16,24],[15,22],[14,18],[12,6],[11,2],[10,-1],[9,-3],[7,-5],[5,-6],[3,-6],[2,-5],[2,-4],[3,-3],[4,-4],[3,-5]] },
8800: { width: 24, points: [[18,19],[6,1],[-1,-1],[3,12],[20,12],[-1,-1],[3,6],[20,6]] },
8834: { width: 24, points: [[20,18],[13,18],[9,17],[7,16],[5,14],[4,11],[4,9],[5,6],[7,4],[9,3],[13,2],[20,2]] },
8835: { width: 24, points: [[4,18],[11,18],[15,17],[17,16],[19,14],[20,11],[20,9],[19,6],[17,4],[15,3],[11,2],[4,2]] },
8853: { width: 20, points: [[9,17],[6,16],[4,14],[3,11],[3,9],[4,6],[6,4],[9,3],[11,3],[14,4],[16,6],[17,9],[17,11],[16,14],[14,16],[11,17],[9,17],[-1,-1],[5,10],[15,10],[-1,-1],[10,5],[10,15]] },
8855: { width: 20, points: [[9,17],[6,16],[4,14],[3,11],[3,9],[4,6],[6,4],[9,3],[11,3],[14,4],[16,6],[17,9],[17,11],[16,14],[14,16],[11,17],[9,17],[-1,-1],[6,6],[14,14],[-1,-1],[14,6],[6,14]] },
8857: { width: 20, points: [[9,17],[6,16],[4,14],[3,11],[3,9],[4,6],[6,4],[9,3],[11,3],[14,4],[16,6],[17,9],[17,11],[16,14],[14,16],[11,17],[9,17],[-1,-1],[10,11],[9,10],[10,9],[11,10],[10,11]] },
9737: { width: 27, points: [[12,22],[9,21],[6,19],[4,16],[3,13],[3,10],[4,7],[6,4],[9,2],[12,1],[15,1],[18,2],[21,4],[23,7],[24,10],[24,13],[23,16],[21,19],[18,21],[15,22],[12,22],[-1,-1],[13,13],[12,12],[12,11],[13,10],[14,10],[15,11],[15,12],[14,13],[13,13],[-1,-1],[13,12],[13,11],[14,11],[14,12],[13,12]] },

// Miscellaneous glyphs (EAM)

176: { width: 14, points: [[6,22],[4,21],[3,19],[3,17],[4,15],[6,14],[8,14],[10,15],[11,17],[11,19],[10,21],[8,22],[6,22]] },
177: { width: 20, points: [[10,15],[10,5],[-1,-1],[4,10],[16,10],[-1,-1],[4,2],[16,2]] },
181: { width: 0, points: [[-99,956]] },
183: { width: 10, points: [[5,11],[4,10],[5,9],[6,10],[5,11]] },
215: { width: 20, points: [[4,16],[16,4],[-1,-1],[4,4],[16,16]] },
402: { width: 15, points: [[15,21],[14,20],[15,19],[16,20],[16,21],[15,22],[13,22],[11,21],[10,20],[9,18],[8,15],[5,1],[4,-3],[3,-5],[-1,-1],[13,22],[11,20],[10,18],[9,14],[7,5],[6,1],[5,-2],[4,-4],[3,-5],[1,-6],[-1,-6],[-2,-5],[-2,-4],[-1,-3],[0,-4],[-1,-5],[-1,-1],[4,15],[14,15]] },
8242: { width: 8, points: [[5,24],[3,16],[-1,-1],[3,16],[6,24]] },
8243: { width: 11, points: [[4,24],[2,16],[-1,-1],[2,16],[5,24],[-1,-1],[9,24],[7,16],[-1,-1],[7,16],[10,24]] },
8463: { width: 21, points: [[9,22],[3,1],[-1,-1],[5,7],[7,11],[9,13],[11,14],[13,14],[15,14],[16,12],[16,10],[14,5],[14,2],[15,1],[19,3],[-1,-1],[7,21],[9,22],[-1,-1],[4,15],[14,20]] },
8491: { width: 0, points: [[-99,197]] },
8495: { width: 18, points: [[4,6],[8,7],[11,8],[14,10],[15,12],[14,14],[12,15],[9,15],[6,14],[4,11],[3,8],[3,5],[4,3],[5,2],[7,1],[9,1],[12,2],[14,4],[-1,-1],[9,15],[7,14],[5,11],[4,8],[4,4],[5,2]] },

// Used to indicate missing glyph
129: { width: 18, points: [[2,-2],[2,21],[16,21],[16,-2],[2,-2]] }
};


CanvasTextFunctions.letter = function (ch)
{
    glyph = CanvasTextFunctions.letters[ch];

    // EAM - Draw an empty box for undefined glyphs
    if (glyph == undefined)
	glyph = CanvasTextFunctions.letters[129];

    return glyph;
}

CanvasTextFunctions.ascent = function( font, size)
{
    return size;
}

CanvasTextFunctions.descent = function( font, size)
{
    return 7.0*size/25.0;
}

CanvasTextFunctions.measure = function( font, size, str)
{
    var total = 0;
    var len = str.length;

    for ( i = 0; i < len; i++) {
	var index = str.charAt(i);
	// EAM deal with non-ascii characaters
	if (index > '~')
	    index = str.charCodeAt(i);

	var c = CanvasTextFunctions.letter(index);
	if (c) total += c.width * size / 25.0;
    }
    return total;
}

CanvasTextFunctions.draw = function(ctx,font,size,x,y,str)
{
    var total = 0;
    var len = str.length;
    var mag = size / 25.0;
    var composite = 0;

    ctx.save();
    ctx.lineCap = "round";
    ctx.lineWidth = 2.0 * mag;

    for ( i = 0; i < len; i++) {
	var index = str.charAt(i);

	// EAM deal with non-ascii characaters
	if (index > '~')
	    index = str.charCodeAt(i);

	// EAM allow composing characters
	if (composite != 0) {
	    index = composite;
	    composite = 0;
	}

	var c = CanvasTextFunctions.letter(index);
	if ( !c) continue;

	ctx.beginPath();

	var penUp = 1;
	var needStroke = 0;
	for ( j = 0; j < c.points.length; j++) {
	    var a = c.points[j];
	    if ( a[0] == -1 && a[1] == -1) {
		penUp = 1;
		continue;
	    }
	    if ( a[0] == -99 ) {
		composite = a[1];
		i--;
		break;
	    }
	    if ( penUp) {
		ctx.moveTo( x + a[0]*mag, y - a[1]*mag);
		penUp = false;
	    } else {
		ctx.lineTo( x + a[0]*mag, y - a[1]*mag);
	    }
	}
	ctx.stroke();
	x += c.width*mag;
    }
    ctx.restore();
    return total;
}

CanvasTextFunctions.enable = function( ctx)
{
    ctx.drawText = function(font,size,x,y,text) { return CanvasTextFunctions.draw( ctx, font,size,x,y,text); };
    ctx.measureText = function(font,size,text) { return CanvasTextFunctions.measure( font,size,text); };
    ctx.fontAscent = function(font,size) { return CanvasTextFunctions.ascent(font,size); }
    ctx.fontDescent = function(font,size) { return CanvasTextFunctions.descent(font,size); }

    ctx.drawTextRight = function(font,size,x,y,text) { 
	var w = CanvasTextFunctions.measure(font,size,text);
	return CanvasTextFunctions.draw( ctx, font,size,x-w,y,text); 
    };
    ctx.drawTextCenter = function(font,size,x,y,text) { 
	var w = CanvasTextFunctions.measure(font,size,text);
	return CanvasTextFunctions.draw( ctx, font,size,x-w/2,y,text); 
    };
}

