import { python, NamedArgument } from "https://deno.land/x/python@0.1.4/mod.ts"

const torch = python.import("torch");
let x = torch.tensor([1.0,2.0], new NamedArgument("requires_grad", true), new NamedArgument("dtype",torch.float))
console.log('x=', x)

let step = 0.01
for (let i=0; i<500; i++) {
    let z = x.norm()
    console.log('0:x.grad=', x.grad)
    z.backward()
    torch.no_grad()
    console.log('1:x.grad=', x.grad)
    console.log('x.grad.__mul__(step)=', x.grad.__mul__(step))
    console.log('x.__rsub__(x.grad.__mul__(step))=', x.__rsub__(x.grad.__mul__(step)))
    let x2 = x.__rsub__(x.grad.__mul__(step)) // 這行完成似乎創造了新物件，而非修改了 x
    // console.log('2:x.grad=', x.grad)
    // x.value = x2.value
    console.log('3:x=', x)
    x.grad.zero_()
}
console.log('x=', x)
