# CodeEval's DNA Alignment problem

I wrote this code to solve CodeEval's DNA Alignment challenge, the 
current hardest problem on the site.  It took about 20 hours, from 
figuring out the algorithm to having a finished, working piece of code.

However, the algorithm is far too slow for DNA strings that are of
length around 400 letters long.

Despite that, I'm happy with it because the algorithm I came up with is pretty
clever.  Instead of generating the impossibly vast number of permutations of 
letters (factorial of 400), it only generates those where the letters are kept 
in the same order, as requested by the problem.  Despite that being the tiniest 
fraction of those possible permutations - and by tiny fraction I mean about 

1.33768 × 10^(-754)

...despite that, it's still too slow for CodeEval's site to 
give me the credit for it.  

Oh well.

So, I'm trying a much simpler idea now, and using 
this code to give me answers to smaller problems, 
with which I can test my new ideas.  

Btw, that number above in words
is 1.33768/(10 million billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion billion billion
billion billion)
