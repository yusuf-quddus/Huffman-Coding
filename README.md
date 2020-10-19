# Huffman-Coding
Using Huffman Coding algorithms to decrypt binary files, and compress and encode text. Assignment for CIS29 Advanced C++ class.

## Huffman Encoding
Diagram explains how text is encoded and decoded. Encoding and decoding uses a binary tree generated from a priority queue that orders charecters by frequency. 
<img width="1440" alt="Huffman Tree" src="https://i.stack.imgur.com/1fEJE.png">

## Decrypted Text from Binary File "Compressed.bin"
Stay Hungry, Stay Foolish.  I am honored to be with you today at your 
commencement from one of the finest universities in the world. I never 
graduated from college. Truth be told, this is the closest I've ever 
gotten to a college graduation. Today I want to tell you three stories 
from my life. That's it. No big deal. Just three stories... When I was 
young, there was an amazing publication called The Whole Earth Catalog, 
which was one of the bibles of my generation. It was created by a fellow 
named Stewart Brand not far from here in Menlo Park, and he brought it 
to life with his poetic touch. This was in the late 1960s, before personal
computers and desktop publishing, so it was all made with typewriters, 
scissors, and polaroid cameras. It was sort of like Google in paperback 
form, 35 years before Google came along it was idealistic, and overflowing
with neat tools and great notions.  Stewart and his team put out several 
issues of The Whole Earth Catalog, and then when it had run its course, they 
put out a final issue. It was the mid 1970s, and I was your age. On the back 
cover of their final issue was a photograph of an early morning country road, 
the kind you might find yourself hitchhiking on if you were so adventurous. 
Beneath it were the words "Stay Hungry. Stay Foolish." It was their farewell 
message as they signed off. Stay Hungry. Stay Foolish. And I have always 
wished that for myself. And now, as you graduate to begin anew, I wish that 
for you. Steve Jobs  h


## Queue Tree mapping
The tree with generated bit strings 
```bash
Leaf: <h> 00000
Leaf: <3> 00001
Leaf: <p> 00010
Leaf: <w> 000110
Leaf: <f> 000111
Leaf: <r> 0010
Leaf: <o> 0011
Leaf: <c> 01000
Leaf: <0> 01001
Leaf: <d> 01010
Leaf: <z> 0101100
Leaf: <M> 0101101000
Leaf: <T> 0101101001
Leaf: <[> 0101101010000000
Leaf: <]> 0101101010000001
Leaf: <\> 0101101010000010
Leaf: <)> 0101101010000011
Leaf: <+> 010110101000010
Leaf: <'> 0101101010000110
Leaf: <&> 0101101010000111
Leaf: <$> 0101101010001
Leaf: <-> 010110101001
Leaf: <F> 01011010101
Leaf: <B> 0101101011
Leaf: <q> 01011011
Leaf: <y> 010111
Leaf: <m> 01100
Leaf: <2> 01101
Leaf: <7> 011100
Leaf: <8> 011101
Leaf: <v> 0111100
Leaf: <j> 0111101
Leaf: <6> 011111
Leaf: <e> 1000
Leaf: <9> 100100
Leaf: <g> 100101
Leaf: <l> 10011
Leaf: <a> 1010
Leaf: <5> 101100
Leaf: <4> 101101
Leaf: <t> 10111
Leaf: < > 1100
Leaf: <k> 110100
Leaf: <R> 1101010000
Leaf: <K> 11010100010
Leaf: <V> 110101000110
Leaf: <@> 110101000111
Leaf: <E> 1101010010
Leaf: <*> 110101001100
Leaf: <_> 1101010011010
Leaf: <=> 1101010011011000
Leaf: <~> 1101010011011001
Leaf: </> 110101001101101
Leaf: <,> 110101001101110
Leaf: <>> 1101010011011110000
Leaf: <"> 1101010011011110001
Leaf: <<> 110101001101111001
Leaf: <(> 110101001101111010
Leaf: <'> 11010100110111101100
Leaf: <{> 11010100110111101101
Leaf: <|> 11010100110111101110
Leaf: <}> 11010100110111101111
Leaf: <%> 1101010011011111
Leaf: <G> 11010100111
Leaf: <S> 1101010100
Leaf: <H> 11010101010
Leaf: <Y> 110101010110
Leaf: <X> 1101010101110
Leaf: <Q> 1101010101111
Leaf: <!> 110101011000
Leaf: <.> 110101011001
Leaf: <W> 110101011010
Leaf: <:> 1101010110110000
Leaf: <^> 1101010110110001
Leaf: <;> 1101010110110010
Leaf: <?> 1101010110110011
Leaf: <#> 11010101101101
Leaf: <Z> 1101010110111
Leaf: <A> 1101010111
Leaf: <x> 11010110
Leaf: <C> 11010111000
Leaf: <D> 11010111001
Leaf: <I> 11010111010
Leaf: <U> 110101110110
Leaf: <J> 110101110111
Leaf: <O> 11010111100
Leaf: <P> 11010111101
Leaf: <N> 11010111110
Leaf: <L> 11010111111
Leaf: <1> 11011
Leaf: <u> 111000
Leaf: <b> 111001
Leaf: <n> 11101
Leaf: <s> 11110
Leaf: <i> 11111
```
