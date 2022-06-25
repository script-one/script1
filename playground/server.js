import { Application, Router } from "https://deno.land/x/oak/mod.ts";

const router = new Router();
router
  .get("/", (context) => {
    context.response.body = "Hello, world!";
  })
  .get("/trans/:code", async (context) => {
    if (context?.params?.code) {
      let target = await translate(context?.params?.code)
      context.response.body = target
    }
  });

const app = new Application();

app.use(async (context, next) => {
  try {
    await context.send({
      root: `${Deno.cwd()}`,
      index: "index.html",
    });
  } catch {
    await next();
  }
});


app.use(router.routes());
app.use(router.allowedMethods());

await app.listen({ port: 8000 });


// source code to target code
async function translate(code)  {
    console.log("source code", code)
    await Deno.writeTextFile("./hello.s1", code);
    console.log("File written to ./hello.s1");
    // define command used to create the subprocess
    const cmd = ["../s1", "./hello.s1", "-o", "./hello.js"];
    // create subprocess
    const p = await Deno.run({ cmd });
    // await its completion
    await p.status();
    const text = await Deno.readTextFile("./hello.js");
    console.log("File read from ./hello.js");
    console.log("target code", text)
  return text
}