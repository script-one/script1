// --allow-run
const cmd = Deno.run({
  cmd: ["python3", "callee.py"], 
  stdout: "piped",
  stderr: "piped"
});

const output = await cmd.output() // "piped" must be set
const outStr = new TextDecoder().decode(output);

const error = await cmd.stderrOutput();
const errorStr = new TextDecoder().decode(error);

cmd.close(); // Don't forget to close it

console.log(outStr, errorStr);
