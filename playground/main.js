import { createEditor, createModel } from "/editor.js";

window.editor = await createEditor(document.querySelector(".source-editor"));
var model = await createModel("mod.ts", `log('Hello, world!')\n`);

await window.editor.setModel(model);


    globalThis.target = await createEditor(document.querySelector(".target-editor"));

