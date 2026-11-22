#!/usr/bin/env python3
"""Cong cu xem file golden .txt va trich tensor tu safetensors (khong can cai them thu vien).

  py tools/golden_tools.py inspect data/attn.hc_pre.y.txt
  py tools/golden_tools.py weights <file .safetensors | thu muc checkpoint>
  py tools/golden_tools.py weights <...> --key <ten tensor> --out data/w_norm.txt
"""
import argparse
import glob
import json
import os
import struct
import sys


def inspect_txt(path, n_show=8):
    count, first, kinds = 0, [], set()
    with open(path, encoding="utf-8") as f:
        for line in f:
            for tok in line.replace(",", " ").split():
                count += 1
                if len(first) < n_show:
                    first.append(tok)
                kinds.add("hex" if tok.lower().startswith("0x") else "thap phan")
    print(f"file        : {path}")
    print(f"so gia tri  : {count}")
    print(f"dinh dang   : {', '.join(sorted(kinds)) or '(rong)'}")
    print(f"{n_show} so dau   : {first}")
    for d in (4096, 16384):
        if count % d == 0:
            print(f"chia het cho {d}: {count // d} hang x {d} cot")


def read_header(path):
    with open(path, "rb") as f:
        n = struct.unpack("<Q", f.read(8))[0]
        header = json.loads(f.read(n))
    return header, 8 + n


def read_tensor(path, name):
    """Tra ve (danh sach float, shape). Chi doc dung phan byte cua tensor nay."""
    header, base = read_header(path)
    info = header[name]
    begin, end = info["data_offsets"]
    with open(path, "rb") as f:
        f.seek(base + begin)
        raw = f.read(end - begin)
    dt = info["dtype"]
    if dt == "BF16":                                  # bf16 = 16 bit cao cua fp32
        u16 = struct.unpack("<%dH" % (len(raw) // 2), raw)
        vals = [struct.unpack("<f", struct.pack("<I", v << 16))[0] for v in u16]
    elif dt == "F32":
        vals = list(struct.unpack("<%df" % (len(raw) // 4), raw))
    elif dt == "F16":
        vals = list(struct.unpack("<%de" % (len(raw) // 2), raw))
    else:
        sys.exit(f"dtype {dt} chua ho tro")
    return vals, info["shape"]


def shards_of(path):
    if os.path.isfile(path):
        return [path]
    return sorted(glob.glob(os.path.join(path, "*.safetensors")))


def weights(path, key, out, grep):
    shards = shards_of(path)
    if not shards:
        sys.exit(f"khong tim thay file .safetensors o {path}")
    found = {}
    for s in shards:
        header, _ = read_header(s)                    # chi doc phan dau file, rat nhanh
        for k, v in header.items():
            if k != "__metadata__" and grep.lower() in k.lower():
                found[k] = (s, v["dtype"], v["shape"])
    if key is None:
        print(f"{len(found)} tensor co '{grep}' trong ten:")
        for k, (s, dt, sh) in sorted(found.items()):
            print(f"  {k}   {dt} {sh}   [{os.path.basename(s)}]")
        print("\nChon 1 ten roi chay lai voi --key <ten> --out <file.txt>")
        return
    if key in found:
        shard = found[key][0]
    else:
        hit = [s for s in shards if key in read_header(s)[0]]
        if not hit:
            sys.exit(f"khong co tensor '{key}'")
        shard = hit[0]
    vals, shape = read_tensor(shard, key)
    with open(out, "w", encoding="utf-8") as f:
        f.write("\n".join("%.9g" % v for v in vals) + "\n")
    print(f"da ghi {len(vals)} gia tri (shape {shape}) tu '{key}' -> {out}")
    print(f"8 so dau: {vals[:8]}")


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    a = sub.add_parser("inspect")
    a.add_argument("txt")
    b = sub.add_parser("weights")
    b.add_argument("path")
    b.add_argument("--key")
    b.add_argument("--out", default="w_norm.txt")
    b.add_argument("--grep", default="norm")
    args = ap.parse_args()
    if args.cmd == "inspect":
        inspect_txt(args.txt)
    else:
        weights(args.path, args.key, args.out, args.grep)


if __name__ == "__main__":
    main()
