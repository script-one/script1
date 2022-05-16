import 'https://deno.land/std/hash/mod.ts' as H

fn hash(text) {
  h1 := H.createHash('sha256')
  h1.update(text)
  return str(h1)
}

record := {
  nonce: 0,
  data: 'john => mary $2.7',
}

json := JSON.stringify(record, null, 2)
print('json=', json)

digest := hash(json)
print('digest=', digest)