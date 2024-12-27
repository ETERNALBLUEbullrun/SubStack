(C) 2024 Swudu Susuwu, dual licenses: choose [_GPLv2_](./LICENSE_GPLv2) or [_Apache 2_](./LICENSE) (allows all uses).

*Notice*: You switched to the [_experimental_](https://github.com/SwuduSusuwu/SubStack/blob/experimental/) branch, which has the newest features, but is unstable, and has much use of `git rebase` force pushes (which require you to use `git pull --rebase`); use [_trunk_ branch](https://github.com/SwuduSusuwu/SubStack/blob/trunk/hooks/README.md#table-of-contents) (`git switch trunk`) for code which is more stable plus has more support.
- This `experimental` branch is for [beta tests](#beta-testexperimental-builds)/[continuous integration](https://google.com?q=continuous-integration-branch).
# [Table of Contents](../README.md#table-of-contents)
- [Purposes](#purposes)
# Purposes
[`./hooks/`](./) is `git` scripts ([`man githooks`](https://git-scm.com/docs/githooks)) which assist you; install with `cp -ra ./hooks/* ./.git/hooks/`.
- [`./hooks/pre-commit`](./pre-commit) is [custom `pre-commit`](https://git-scm.com/book/en/v2/Customizing-Git-Git-Hooks) (produces `./tags`) + [`.git/hooks/pre-commit.sample` (scans for non-ASCII filenames, conflict markers or whitespace errors)](https://github.com/auth0/gitzero/blob/master/tests/example/_git/hooks/pre-commit.sample)

[`./tags`](../tags) is [an _IntelliSense_ alternative for editors such as `vim`](https://vi.stackexchange.com/a/45044) (stores data for [autocompletion use](https://vim.fandom.com/wiki/Any_word_completion), or to [jump to declarations through tags](https://dev.to/iggredible/how-to-use-tags-in-vim-to-jump-to-definitions-quickly-2g28)). Included for systems without [`ctags`](https://github.com/universal-ctags/ctags?tab=readme-ov-file#universal-ctags) (which produces this).

