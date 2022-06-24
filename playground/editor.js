import { editor, Uri } from "https://esm.sh/monaco-editor@0.33.0";
import editorWorker from "https://esm.sh/monaco-editor@0.33.0/esm/vs/editor/editor.worker?worker";
import tsWorker from "https://esm.sh/monaco-editor@0.33.0/esm/vs/language/typescript/ts.worker?worker";

// deno-lint-ignore ban-ts-comment
// @ts-ignore
self.MonacoEnvironment = {
  getWorker(_, label) {
    if (label === "typescript" || label === "javascript") {
      return tsWorker();
    }
    return editorWorker();
  },
};

export function createModel(name, source) {
  const lang = getLanguage(name);
  if (!lang) {
    return null;
  }

  const uri = Uri.parse(`file:///src/${name}`);
  const model = editor.createModel(source, lang, uri);
  return model;
}

export function createEditor(container, readOnly) {
  return editor.create(container, {
    readOnly,
    automaticLayout: true,
    contextmenu: true,
    fontSize: 14,
    lineHeight: 18,
    lineNumbersMinChars: 2,
    minimap: { enabled: false },
    scrollBeyondLastLine: false,
    smoothScrolling: true,
    scrollbar: {
      useShadows: false,
      verticalScrollbarSize: 10,
      horizontalScrollbarSize: 10,
    },
    overviewRulerLanes: 0,
  });
}

function getLanguage(name) {
  switch (name.slice(name.lastIndexOf(".") + 1).toLowerCase()) {
    case "ts":
    case "tsx":
      return "typescript";
    case "js":
    case "jsx":
      return "javascript";
  }
  return null;
}