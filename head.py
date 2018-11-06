from re import match

DEFINITION = r'([a-zA-Z0-9_]+)\s([a-zA-Z0-9_]+)\('

with open('head') as fin, open('head.h', 'w') as hout, open('head.cpp', 'w') as cout:
    template = ''
    for i, line in enumerate(fin):
        line = line.strip()


        if line.startswith('template'):
            template = line

        d = match(DEFINITION, line)
        if d:
            type, name = d.groups()
            fout = hout if template else cout

            if template:
                hout.write('\t')
                hout.write(template)
                hout.write('\n')
                hout.write('\t')
                hout.write(line)
                hout.write(' override ;\n')
                template = ''
            else:
                hout.write('\t')
                hout.write(line)
                hout.write(' override ;\n')
                cout.write(line)
                cout.write('\n')



            if name.startswith('HICANN'):
                code = 'auto jtag = extoll->jtag(node);', '', 'return true;'
            elif name.startswith('DNC'):
                code = f'throw std::runtime_error("Deprecated: {name}");',
            else:
                code = f'throw std::runtime_error("Not Implemented: {name}");',
            if fout is hout:
                fout.write('\t{\n')
                for i in code:
                    fout.write('\t\t')
                    fout.write(i)
                    fout.write('\n')
                fout.write('\t}\n\n')
            else:
                fout.write('{\n')
                for i in code:
                    fout.write('\t')
                    fout.write(i)
                    fout.write('\n')
                fout.write('}\n\n')
