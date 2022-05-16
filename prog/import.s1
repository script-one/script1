import 'https://deno.land/std/hash/mod.ts' as H

fn hash(text) {
  h1 := H.createHash('sha256')
  h1.update(text)
  return str(h1)
}

print('hash(hello)=', hash('hello'))
