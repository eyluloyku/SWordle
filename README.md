<h1 align="center">SWordle</h1>

# Introduction:
In this project, Sabancı version of the world-wide internet sensation “Wordle” is implemented. The regular game challenges the users to guess a word, and if they can guess the correct word in six attempts or less, they win. Every time the user guesses a word, the game will give hints about the correctness of the guess. When a user guesses a word, the letters of the guessed word will be colored with one of three colors: green, yellow, and black, and each of these colors has different meanings. For each letter in the guessed word, if the letter falls in the same position in the correct word, it will be colored green. If the letter is in the correct word, but is in the wrong position, it will be colored yellow. Finally, if the letter does not occur at all in the correct word, it will be colored black. Here’s an example. Let’s assume the word the user needs to guess is “trade”. First, user tries the word “ready” as shown in Figure 1.

<p align="center">
  <img src="https://user-images.githubusercontent.com/116841987/202853161-2d52aa87-f094-40a1-8d61-7aa311707453.png" />
</p>
<p align="center">
Figure 1: User entered “ready” when the correct word is trade
</p>

As you can see in Figure 1, the letter “y” is colored black because it does not occur in the word “trade”. The letters “r” and “e” are colored yellow because they occur in “trade”, but in wrong positions. Finally, the letters “a” and “d” are in the correct positions, so they are colored green.
Next, the user tries “grade” (Figure 2). Only one letter is wrong!
<p align="center">
  <img src="https://user-images.githubusercontent.com/116841987/202853181-49d7075b-b04d-4213-9679-541d4d7c8e33.png" />
</p>
<p align="center">
Figure 2: user entered “grade” when the correct word is “trade”.
</p>

Finally, the user tries “trade” and finds the correct word, it is a win (Figure 3)!
<p align="center">
  <img src="https://user-images.githubusercontent.com/116841987/202853192-cc8ac1d5-c014-41e3-94dd-8c91488ae745.png" />
</p>
<p align="center">

The game that is built will be different than the regular Wordle, so we rename it as SWordle (Sabancı version of Wordle). Mainly, there are four differences:
1. You will be able to specify the number of attempts that the user can try; it could be more or less than 6 attempts.
2. The words that the user will guess don’t need to be 5 letters long. It can be shorter or longer.
3. There are some extra input checks for the guesses that regular Wordle does not have (see below).
4. Regular Wordle enforces to use a meaningful word as the guess, but in SWordle, we do not have such a rule.
