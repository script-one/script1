// source file: prog/_server.s1
import '../sys/s1.js'

let app=new Server();                              // (1) 
export function hello(ctx)                         // (3) 
{                                                  // (3) 
    ctx.response.body='Hello World!';              // (4) 
}                                                  // (3) 
app.use(hello);                                    // (7) 
log('start at : http://127.0.0.1:3001');           // (9) 
await app.listen({'port':3001});                   // (10) 
if (typeof main == 'function') main()
