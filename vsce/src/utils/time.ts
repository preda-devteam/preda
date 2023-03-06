export const MINUTE = 60 * 1000;
export const HOUR = MINUTE * 60;
export const DAY = HOUR * 24;
export const WEEK = 7 * DAY;
export const MONTH = DAY * 30;
export const PERMANENT = MONTH * 2;

export function padStart(num: any, len: number = 2, ch: string = "0"): string {
  let output = `${num}`;

  while (output.length < len) {
    output = `${ch}${output}`;
  }
  return output;
}

export function formatTime(
  time: number,
  formatStr: string = "YYYY-MM-DD"
): string {
  const d = new Date(time);
  return formatStr
    .replace("YYYY", d.getFullYear().toString())
    .replace("MM", padStart(d.getMonth() + 1))
    .replace("DD", padStart(d.getDate()))
    .replace("HH", padStart(d.getHours()))
    .replace("mm", padStart(d.getMinutes()))
    .replace("ss", padStart(d.getSeconds()))
    .replace("SS", d.getMilliseconds() + "");
}
