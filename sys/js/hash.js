import * as H from 'https://deno.land/std/hash/mod.ts'

export function hash(text, method='sha256') {
  let h1 = H.createHash(method)
  h1.update(text)
  return h1.toString()
}
