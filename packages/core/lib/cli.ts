import fs from 'fs/promises';
import YAML from 'yaml';

import { generate } from "./combo";
import { OptionsInput } from "./combo/options";
import { makeSettings } from './combo';

const makeOptions = async (args: string[]): Promise<OptionsInput> => {
  const opts: OptionsInput = {};
  opts.settings = {};

  for (let i = 0; i < args.length; i++) {
    const opt = args[i];
    switch (opt) {
    case "--debug":
      opts.debug = true;
      break;
    case "--seed":
      opts.seed = args[++i];
      break;
    case "--random":
      opts.random = { enabled: true };
      break;
    case "--config": {
      const configFile = await fs.readFile(args[++i]);
      const config = YAML.parse(configFile.toString());
      if (config.settings) {
        opts.settings = config.settings;
      }
      if (config.cosmetics) {
        opts.cosmetics = config.cosmetics;
      }
      break;
    }
    case "--patch": {
      const patch = await fs.readFile(args[++i]);
      opts.patch = patch;
      break;
    }
    case "--settings": {
      const newBuf = Buffer.from(args[++i], 'base64');
      const newPartialSettings = JSON.parse(newBuf.toString());
      opts.settings = makeSettings(newPartialSettings);
      break;
    }
    default:
      throw new Error(`Unknown option: ${opt}`);
    }
  }
  return opts;
};

function writeFiles(data: (Buffer | string)[], name: string, ext: string) {
  if (data.length === 1) {
    return [fs.writeFile(`${name}.${ext}`, data[0])];
  }

  return data.map((x, i) => {
    return fs.writeFile(`${name}-${i+1}.${ext}`, x);
  });
}

const main = async () => {
  const opts = await makeOptions(process.argv.slice(2));
  const [oot, mm] = await Promise.all([
    fs.readFile('../../roms/oot.z64'),
    fs.readFile('../../roms/mm.z64'),
  ]);
  const gen = generate({ oot, mm, opts });
  const { roms, log, hash, patches } = await gen.run();
  await fs.mkdir('out', { recursive: true });
  const promises: Promise<unknown>[] = [];
  const suffix =  opts.debug ? "" : `-${hash}`

  promises.push(...writeFiles(roms, `out/OoTMM${suffix}`, 'z64'));
  promises.push(...writeFiles(patches, `out/OoTMM-Patch${suffix}`, 'ootmm'));
  if (log)
    promises.push(...writeFiles([log], `out/OoTMM-spoiler${suffix}`, 'txt'));

  return Promise.all(promises);
}

main().catch((err) => {
  console.error(err);
  process.exit(1);
});

