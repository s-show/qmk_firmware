import { defineConfig } from "jsr:@yuki-yano/zeno";

export default defineConfig(({ projectRoot, currentDirectory }) => ({
  snippets: [
    {
      name: "compile",
      keyword: "compile",
      snippet: "qmk compile -kb {{keyboard_name}} -km {{keymap}}",
    },
  ],
}));

