def needleman_wunsch_all(seq1, seq2, match_score=1, mismatch_penalty=-1, gap_penalty=-1):
    n = len(seq1)
    m = len(seq2)

    # Initialize the scoring matrix
    score_matrix = [[0 for j in range(m + 1)] for i in range(n + 1)]
    for i in range(n + 1):
        score_matrix[i][0] = i * gap_penalty
    for j in range(m + 1):
        score_matrix[0][j] = j * gap_penalty

    # Fill the scoring matrix
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            match = score_matrix[i - 1][j - 1] + (match_score if seq1[i - 1] == seq2[j - 1] else mismatch_penalty)
            delete = score_matrix[i - 1][j] + gap_penalty
            insert = score_matrix[i][j - 1] + gap_penalty
            score_matrix[i][j] = max(match, delete, insert)


    def traceback(i, j):
        if i == 0 and j == 0:
            return [("", "")]
        alignments = []
        if i > 0 and score_matrix[i][j] == score_matrix[i - 1][j] + gap_penalty:
            for alignment in traceback(i - 1, j):
                alignments.append((alignment[0] + seq1[i - 1], alignment[1] + '-'))
        if j > 0 and score_matrix[i][j] == score_matrix[i][j - 1] + gap_penalty:
            for alignment in traceback(i, j - 1):
                alignments.append((alignment[0] + '-', alignment[1] + seq2[j - 1]))
        if i > 0 and j > 0 and score_matrix[i][j] == score_matrix[i - 1][j - 1] + (match_score if seq1[i - 1] == seq2[j - 1] else mismatch_penalty):
            for alignment in traceback(i - 1, j - 1):
                alignments.append((alignment[0] + seq1[i - 1], alignment[1] + seq2[j - 1]))
        return alignments

    alignments = traceback(n, m)
    return alignments, score_matrix[n][m]


# Test the function

if __name__ == '__main__':

    while True:

        seq1 = input("enter the sequence1 : ")
        seq2 = input("enter the sequence2 : ")
        
        alignments, score = needleman_wunsch_all(seq1, seq2)
        
        print("Global Alignments:")
        for align1, align2 in alignments:
            print(align1)
            print(align2)
            print()
        print("Score:", score)


