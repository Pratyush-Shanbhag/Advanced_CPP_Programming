s = """
P1R5I;?;5.5RQ2(T9';')H-1E!NCAJ'SIDKDR)(SWPTOVO2HGS6XKY!B!'1?3?IDFZYL.J2!4-
KJNTTFT;TNUUMN1CC2U9V5I.Z81 04-66T "DX(-I1?HHONF"TTJQQW?ZV-
2RPCTXU2V.J91MY('97.6;6-X)CJ(DECBAKAD BPG!RUKM0XAO215..X.K!Z63;36SZ6 
,BF!0(AMB"N7CUEO,H1NY0MMGCB697Z5ZJ3!M;(!224?IV8,GI0BFHQI6CMQ XJDX?OZ-
WY7BQ8RSWWJ!31NY'A'.).VF,GI1.2BN5EP8" QTRGJYZ-XPA5R68Z5ZJVL9Y179?7BU68("-
JP2MI5(QFHNL;C!?ZOM'LL4VQE59X63!1N;5QA 8UEGE)C)1L-
MO6FQ9TICW!F(O2VKYBW8SWVI(9(81O15R-?58..Y-
D1ALIG)QGNN.CQH?NH3N"481DR44;Y,!X)7!!"S1U"",YL'K"3?5'LKOUUGU!FTK-
XXPB9W8XGS69?42(P(6"B''W5Y!N!)IN5PEC9JVFJI?2V2UNYK6DQUG.75ZM"6839SF5DWJ(-
;'33CA6QFD 
DQPTZZLZ'MZ6YREV564J!42O9A598U6".Y,.IJR4JJ7'9CPPYIWYH1RYYB6VP9G0.J3917-" ( 
E!E?9.B(2'LJI7RGAU,RJ?ZOM'R5YN1GF ZXJX 9!""6"T;DWF9-
!1LH4C)SC9PBUVII(0PN"464W2WG.X,!MM.!Q4)("FF,FZ-,K3J(OPCC JV;2JZ--
UO34CW7F157(8NM5;C6D8BXW8 DKK2MOMEKE-
S.KQXJRSQPOYORD.482IX?;5.5PDE,;VI?;C0')3ONAA8GIT,PEYNLUJ3TONZEQ4VIW,",);.?
9,7VE-)ABJ2MI5DBJO 
CTHEP(VVN"ZRC7WUG47,!L064594D(EWB!Z)(JF?I6"GOHFTV(?KUQPWLCCS2YX4TJ)W?NZP3 
-, DXA 
;'AG'76B'BH.MH2XZYWTOA3R30QTWWJVLZ5Z)14B8CW(BZJ')3G"OP'FE.YLXM(HVX3SQ4DRXR
9TW!0!N24"6"(;",,Z,P2MB"6J'BHJPHW?XV1X1A4R78Y4Y.JV90NA8- ( U6EF D-
)F'IPP8SHBV;0JXL-Y1P7V2982(IY;?XZ 8'977U7.HL?(F3NCA7QDNEGU!FTK-
2RPB4SRUZ;X.LL5.O'86S85C-LZO(;KM5KC8VWJK?!Y0YQWQA815ZUUHT;KX!6-09?AT7" 
,Y,I)!EDJD8GEBFTYFX0M02AU0DQ1V.V160AN!0-
,TT;'W8,;"LBII6QM9MBVKIRG0QLSLZ5FER2W,W271BO?1';T5)EBYG??KODPBB9LJPJYNY00'
KYPCQWU9 IW2W9;7!!"UT5' X9IJI!)OAA8SAMGQX?H5-JZ031ORXZ5ZJ)4 .3)'R)9U6W 
CBFC)R5'OMRSXQUH?V178VPB62974S5Y8?M53.4R4HUE!,Y;."DR5PBJDGSCSL(()131TZTM7F
3S,1Z8X)721;S4-9W'C('!2LEEIJR NCGI?NPU'KAZN797R3IW,",)Z;1;GBDWWJ(!H(;L4-
OWOTPIUEUNLZ1"73V7TFV5V.'.(6;;Q"GBD 'F0Z.E(3)MUNSOMQJMXZZ-
135P.D8XV4KJX;A;-0!2!HCEEX"-A(2MOMEKF 
CTHEP(0PNWBBV1E)FAHLK?)?7;7R5A96F,,Z.1E-
NCKA8CBNOII(G1QOAN10QUIRIU8L1932"')(98!8B-;,D3-
"RFAD.VKEY(JW3VOBQS8UT.I;20M(3'" ( 
CV,BFZ?EA"G(87'KLQZMSM)1QOAMYZXUUH88)0!(O'?R687!B?;G0-)KG(J7CMCS1TYOVV1A
"""
#s = "DDEEBWLJFKWPJLZQNRQJ"
#s = "NJDTRNH"
print()
"""a = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
                'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 
                'Z', ' ']"""

a = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        ' ', '.', ',', ';', '!', '?', '(', ')', '-', '\'', '\\', '"']
l = []
for i in range(len(s)-4):
    if ord(s[i]) + 4 == ord(s[i+4]):
        l.append(i+1)
        print(s[i], s[i+4])
loc = -1
n = 0
b = True
c = 0
print(l)
print("count:", len(l))
"""
for i in l:
    for j in range(i, i + 3):
        if j == i:
            print("j==i", j)
            #if i <= 19:
            n = 19 - i
            print("n", n)
            #else:
            #    n = 
        else:
            print("ord(s[j])", a.index(s[j]))
            c = (a.index(s[j]) + n) % (26+j)
            #print(i, c, a[c])
            print(a.index(s[j]) + n)
            if j == i + 1 and a[c] != 'H':
                b = False
                break
            if j == i + 2:
                if a[c] != 'E':
                    b = False
                    break
                else:
                    loc = i

print("loc", loc, s[loc:loc+3])"""


#s = "FEED THE DOG AND CAT"
a2 = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 
'Z', ' ']

#r1 = 0
#r2 = 25
e = 0
l = []
def encrypt(a, s, r1 = 0, r2 = 25):
    e = 0
    for chr in s:
        if chr != '\n':
            e = (a.index(chr) + r1 + r2) % len(a)
            l.append(e)
            r1 += 1
            if r1 % len(a) == len(a) - 1:
                r2 += 1
        else:
            l.append(-1)

    for i in l:
        if i == -1:
            print()
        else:
            print(a[i], end='')

    print()
s = "FEED THE DOG AND CAT"
encrypt(a2, s)


n = 19 - 5
#c = (a.index(s[j]) + n) % (26+j)
c = (l[6] + n) % (26 + 6)
print(c)
print(a2[c])