import random
import itertools as it
import copy


def generate_superseq(subseq, alpha, minlen, maxlen):
    seq = copy.deepcopy(subseq)
    sublen = len(subseq)
    seqlen = random.randint(minlen, maxlen)
    seqpos = sorted(random.sample(list(range(seqlen)), k = seqlen-sublen))
    for i in seqpos:
        seq.insert(i, random.choice(alpha))
    return "".join(seq)


random.seed(100)
lcs_length = 20
dna = ['A', 'C', 'G', 'T']
lcs = random.choices(dna, k=lcs_length)
print(lcs)

x = generate_superseq(lcs, dna, 30, 40)
y = generate_superseq(lcs, dna, 30, 40)

with open("seq_data.txt", 'w') as f:
    f.write(f"{x}\n")
    f.write(f"{y}\n")