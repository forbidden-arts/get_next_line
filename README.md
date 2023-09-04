# get_next_line
<!-- ![dpalmer's 42 stats](https://badge42.vercel.app/api/v2/cli5pb141011308mh1fmi5qrq/stats?cursusId=21&coalitionId=271) -->

![Achievement Unlocked!](./assets/get_next_linem.png)

<!-- ![dpalmer's 42 get_next_line Score](https://badge42.vercel.app/api/v2/cli5pb141011308mh1fmi5qrq/project/2872683) -->

## 🤓 Overview
Ever wanted to read a file line by line? It's conceptually simple, yet technically complicated to implement from scratch. That was the goal (achieved, boom! 🤓) for this second project. In keeping with 42's mantra of 'build everything yourself', these functions (they're actually the same, but split into different files for submission purposes) will read files n-bytes at a time, and continue to do so until they reach a newline character, or the end of the file, and then return that line. Any additional characters read (because you don't always land directly on the character you want) are stored in a buffer, ready to use if the function is called again.

We were not allowed to link any libraries, including the ones that we had previously written, so the functions in get_next_line_utils* are duplicates of what are available in [libft](https://github.com/forbidden-arts/libft).

## 📷 Preview
This function has been integrated into [libft](https://github.com/forbidden-arts/libft) and has been instrumental in parsing  data files, maps, and text. It is not a standalone executable, so there's not much to show, but you are welcome to go through the code and point out where I could tighten up the logic.

## 💻 Compilation
To compile:

_not applicable_

Remove the object files:

_not applicable_

Remove everything:

_not applicable_

### 📝 License
Distributed under the MIT License. See [LICENSE](LICENSE) for more information.
