if vim.fn.has('nvim-0.11') == 1 then
  local lsp_names = { 'ccls' }
  vim.lsp.enable(lsp_names)
  local _, result = pcall(vim.lsp.document_color.enable, true, 0, { style = 'virtual' })
end
vim.fn["ddc#custom#patch_filetype"]({ 'c', 'cpp' }, {
  sourceParams = {
    lsp = {
      enableResolveItem = false,
    }
  }
})

