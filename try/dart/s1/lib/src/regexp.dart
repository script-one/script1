List grep(sexp, text, [groupId=0]) {
    var list = [];
    RegExp exp = RegExp(sexp);
    Iterable<RegExpMatch> matches = exp.allMatches(text);
    for (var m in matches) {
        if (m != null) list.add(m.group(groupId));
    }
    return list;
}