import "https://deno.land/x/oak/mod.ts" as oak

const app = new oak.Application()

app.use(fn(ctx) {
  ctx.response.body = "Hello World!"
})

print('start at : http://127.0.0.1:8000')
await app.listen({ port: 8000 })
