const path = require("path");
const TerserPlugin = require("terser-webpack-plugin");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const getCSSModuleLocalIdent = require("react-dev-utils/getCSSModuleLocalIdent");

const getStyleLoaders = require("./get-loaders");

const isProd = process.env.NODE_ENV === "production";
const cssRegex = /\.css$/;
const cssModuleRegex = /\.module\.css$/;
const sassRegex = /\.(scss|sass)$/;
const sassModuleRegex = /\.module\.(scss|sass)$/;
const extenstionPath = path.resolve(__dirname, "..", "out", "web");
const extenstionURLPath = extenstionPath.split(path.sep).filter(i => i).join('/');

const optimization = !isProd
  ? {
      minimize: false,
    }
  : {
      minimizer: [
        new TerserPlugin({
          parallel: true,
          terserOptions: {
            // https://github.com/webpack-contrib/terser-webpack-plugin#terseroptions
          },
        }),
      ],
    };

module.exports = {
  entry: path.join(__dirname, "index.tsx"),
  resolve: {
    extensions: [".ts", ".tsx", ".js", ".jsx", ".css", ".less"],
    alias: {
      "@": path.join(__dirname),
    },
  },
  devtool: isProd ? false : "inline-source-map",
  externals: { vscode: "vscode" },
  module: {
    rules: [
      {
        test: /\.tsx?$/,
        use: "ts-loader",
        exclude: "/node_modules/",
      },
      {
        oneOf: [
          // "postcss" loader applies autoprefixer to our CSS.
          // "css" loader resolves paths in CSS and adds assets as dependencies.
          // "style" loader turns CSS into JS modules that inject <style> tags.
          // In production, we use MiniCSSExtractPlugin to extract that CSS
          // to a file, but in development "style" loader enables hot editing
          // of CSS.
          // By default we support CSS Modules with the extension .module.css
          {
            test: cssRegex,
            exclude: cssModuleRegex,
            use: getStyleLoaders(
              {
                importLoaders: 1,
                sourceMap: !isProd,
                modules: false,
              },
              "",
              isProd
            ),
            // Don't consider CSS imports dead code even if the
            // containing package claims to have no side effects.
            // Remove this when webpack adds a warning or an error for this.
            // See https://github.com/webpack/webpack/issues/6571
            sideEffects: true,
          },
          {
            test: cssModuleRegex,
            use: getStyleLoaders(
              {
                importLoaders: 1,
                sourceMap: !isProd,
                modules: {
                  mode: "local",
                  getLocalIdent: getCSSModuleLocalIdent,
                },
              },
              "",
              isProd
            ),
          },
          // Opt-in support for SASS (using .scss or .sass extensions).
          // By default we support SASS Modules with the
          // extensions .module.scss or .module.sass
          {
            test: sassRegex,
            exclude: sassModuleRegex,
            use: getStyleLoaders(
              {
                importLoaders: 3,
                sourceMap: !isProd,
                modules: false,
              },
              "sass-loader",
              isProd
            ),
            // Don't consider CSS imports dead code even if the
            // containing package claims to have no side effects.
            // Remove this when webpack adds a warning or an error for this.
            // See https://github.com/webpack/webpack/issues/6571
            sideEffects: true,
          },
          // Adds support for CSS Modules, but using SASS
          // using the extension .module.scss or .module.sass
          {
            test: sassModuleRegex,
            use: getStyleLoaders(
              {
                importLoaders: 3,
                sourceMap: !isProd,
                modules: {
                  mode: "local",
                  getLocalIdent: getCSSModuleLocalIdent,
                },
              },
              "sass-loader",
              isProd
            ),
          },

          {
            // Exclude `js` files to keep "css" loader working as it injects
            // its runtime that would otherwise be processed through "file" loader.
            // Also exclude `html` and `json` extensions so they get processed
            // by webpacks internal loaders.
            exclude: [/^$/, /\.(js|mjs|jsx|ts|tsx|ttf)$/, /\.html$/, /\.json$/],
            type: "asset/resource",
            generator: {
              filename: "[name][ext]",
            },
          },
          {
            test: /\.(ttf)$/,
            type:  "asset/resource",
            generator: {
              filename: "[name][ext]",
              publicPath: "https://file%2B.vscode-resource.vscode-cdn.net/" + extenstionURLPath + '/'
            },
          }
        ],
      },
    ],
  },
  output: {
    filename: "main.js",
    path: extenstionPath,
    publicPath: "{{staticPath}}",
  },
  optimization,
  plugins: [
    isProd &&
      new MiniCssExtractPlugin({
        // Options similar to the same options in webpackOptions.output
        // both options are optional
        filename: "style.css",
      }),
    new HtmlWebpackPlugin({
      template: path.resolve(__dirname, "./index.html"),
      filename: "index.html",
      cache: false,
      inject: true,
      chunks: ["main"],
      // Nerver minify
      minify: !isProd
        ? false
        : {
            removeComments: true,
            collapseWhitespace: true,
            removeRedundantAttributes: true,
            useShortDoctype: true,
            removeEmptyAttributes: true,
            removeStyleLinkTypeAttributes: true,
            keepClosingSlash: true,
            minifyJS: true,
            minifyCSS: true,
            minifyURLs: true,
          },
    }),
  ].filter(Boolean),
};
