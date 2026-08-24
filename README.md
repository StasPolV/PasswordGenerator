# Password Generator

![C++](https://img.shields.io/badge/C%2B%2B-20-00599C?logo=cplusplus&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-%E2%89%A5%206.7-41CD52?logo=qt&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%E2%89%A5%203.28-064F8C?logo=cmake&logoColor=white)

A desktop password generator built with **C++20** and **Qt6** (Widgets), featuring a cryptographically secure random source, guaranteed character-set coverage, and a themeable UI. Built with an MVC-style architecture: the model owns all generation state, the widgets stay passive, and the controller is the only component that knows about both.

> **Cross-platform:** builds and runs on Windows, Linux, and macOS — the codebase has no platform-specific code, relying only on Qt6 and CMake.

## Features

- Adjustable password length from 6 to 32 characters, driven by a linked slider and spin box
- Four toggleable character sets — uppercase, lowercase, digits, and symbols
- Every enabled character set is guaranteed to appear at least once in the result
- Randomness sourced from `QRandomGenerator::system()`, the OS cryptographic RNG, rather than the default seeded generator
- One-click copy to the clipboard; the output field itself is read-only, so a displayed password always matches the settings that produced it
- Custom Qt Style Sheet theme, fully defined in a single `.qss` resource, layered over the Fusion base style for a consistent look across platforms

## Build

**Requirements:** C++20 compiler, CMake ≥ 3.28, Qt6 ≥ 6.7 (`Core`, `Widgets`)

```bash
git clone <repo_url>
cd <project_folder>
cmake -S . -B build -DCMAKE_PREFIX_PATH=<path_to_Qt6>
cmake --build build -j
```

Run the `PasswordGenerator` executable from the `build` folder.

## Tests

Unit tests cover `PasswordGeneratorModel` using GoogleTest, which CMake pulls in through `FetchContent` — the first configure step needs network access. Tests are enabled by default; pass `-DPASSWORD_GENERATOR_BUILD_TESTS=OFF` to skip them.

```bash
ctest --test-dir build --output-on-failure
```

## Notes

**Qt 6.7 is a hard minimum.** The UI connects to `QCheckBox::checkStateChanged`, which replaced the deprecated `stateChanged(int)` in Qt 6.7. On earlier releases the project will not compile.

**The symbol set omits two printable ASCII characters.** `"` (double quote) is excluded because passwords containing it are awkward to paste into shell commands, config files, and CSV exports without escaping. The space character is excluded because it is invisible in the output field and is silently trimmed by a fair number of login forms. Every other ASCII punctuation character is included:

```
!#$%&'()*+,-./:;<=>?@[\]^_{|}~`
```

**At least one character set must stay enabled.** When only one remains checked, its checkbox is disabled rather than reverted after the fact — an empty alphabet never reaches the model. The model still guards against it, but that path is only reachable when constructing `PasswordGeneratorModel` directly in code.

## Roadmap

- [ ] Option to exclude ambiguous characters (`0`/`O`, `1`/`l`/`I`)
- [ ] Password strength indicator based on alphabet size and length
- [ ] User-configurable symbol set instead of the fixed list
- [ ] Persist the last used settings between sessions via `QSettings`
